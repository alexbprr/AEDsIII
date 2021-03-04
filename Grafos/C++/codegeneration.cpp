#include "codegeneration.h"

CodeGeneration::CodeGeneration(Graph *g){
    graph = g; 
    nodes = g->getNodes();
    interactions = g->getInteractions();
    edges = g->getEdges();
}

CodeGeneration::~CodeGeneration(){}

string CodeGeneration::replaceLocalString(string str, string pattern, string newstr){
    size_t len = pattern.length();
    string line, resultstr; 
    istringstream inputStrStream(str);
    while (getline(inputStrStream, line)){
        while (true) {
            size_t pos = line.find(pattern);
            if (pos != string::npos)
                line.replace(pos, len, newstr);
            else 
                break;
        }
        resultstr += line + '\n';
    }  
    return resultstr;
}

void CodeGeneration::replaceString(string pattern, string newstr){
    size_t len = pattern.length();
    string line; 
    istringstream inputStrStream(outputStream.str());
    outputStream.str("");
    while (getline(inputStrStream, line)){
        while (true) {
            size_t pos = line.find(pattern);
            if (pos != string::npos)
                line.replace(pos, len, newstr);
            else 
                break;
        }
        outputStream << line << '\n';
    }    
}

void CodeGeneration::replaceString(string pattern, vector<string> newstrvector){
    size_t len = pattern.length();
    string line, newstr; 
    for (string s: newstrvector){
        if (s == newstrvector.back())
            newstr += s;
        else 
            newstr += s + ", ";
    }
    istringstream inputStrStream(outputStream.str());
    outputStream.str("");    
    while (getline(inputStrStream, line)){
        while (true) {
            size_t pos = line.find(pattern);
            if (pos != string::npos)
                line.replace(pos, len, newstr);
            else 
                break;
        }
        outputStream << line << '\n';
    }    
}

//----------------------ODEs----------------------------
string CodeGeneration::buildNumerator(Interaction *in){
    string numerator; 
    vector<int> posInfl = in->getPositiveInfluences();    
    if (posInfl.size() > 0) {
        numerator = "(";
        if (in->getJoinRule() == 0){
            //Gerar um novo nome de parâmetro sob demanda 
            string pname = paramNames.back();
            numerator += pname;
            in->getEquation()->addParameter(make_pair(pname,defaultValue));
            paramNames.pop_back();
            for (int id: posInfl){
                numerator += "*" + graph->getNode(id)->getName(); 
                in->getEquation()->addVar(id);
            }
        }
        numerator += ")";
    }    
    return numerator; 
}

string CodeGeneration::buildDenominator(Interaction *in){
    string denominator;
    vector<int> negInfl = in->getNegativeInfluences();    
    if (negInfl.size() > 0) {
        denominator = "(1 + ";
        if (in->getJoinRule() == 0){
            //Gerar um novo nome de parâmetro sob demanda 
            string pname = paramNames.back();
            denominator += pname;
            in->getEquation()->addParameter(make_pair(pname,defaultValue));
            paramNames.pop_back();
            for (int id: negInfl) {                
                denominator += "*" + graph->getNode(id)->getName();
                in->getEquation()->addVar(id);
            }
        }
        denominator += ")";
    }    
    return denominator;
}


void CodeGeneration::generateODEIR(){
    for (int j = 100; j >= 0; j--) {
        paramNames.push_back("p" + to_string(j));
    }
    /* 
        vars ... 
        params ... 
        ini ... 
        eqs ... 
    */
    ofstream fp;
    fp.open("models/odemodel.txt", ios::out);
    
    for (Node *n: nodes){
        if (n != nullptr && n->hasInteraction()) {
            string nodename = n->getName();
            //Para nós com status igual a 0, definir o valor inicial 0 
            vars.push_back(make_pair(nodename,n->getInitialValue()));
            varNames.push_back(nodename); 
        }
    }

    //Create equations 
    string newterm, signal; 
    for (Interaction *in: interactions){
        if (in == nullptr) continue; 
        if (in->getStatus() == 0) continue; //The interaction is inactive 
        int idMainNode = in->getMainNode(); 
        if (idMainNode >= 0){
            Node::LinkDirection linkdir = in->getLinkDirection(idMainNode);
            if (linkdir == Node::LinkDirection::fromNode){
                signal = "-";
            }
            else if (linkdir == Node::LinkDirection::toNode){
                signal = "+";
            }
            string eqtext = in->getEquation()->getText(); 
            if (eqtext.empty()){
                //Criar classe para gerar o nome dos parâmetros? 
                string numerator = buildNumerator(in);
                string denominator = buildDenominator(in);
                if (denominator.empty())
                    newterm = signal + numerator; 
                else 
                    newterm = signal + numerator + "/" + denominator; 
            }
            else {
                newterm = signal + eqtext;                 
            }
            nodeEquations[idMainNode].push_back(newterm);
            //cout << "New term: " << newterm << endl; 
        }
        else if (in->getSink() >= 0){
            int idSink = in->getSink(); 
            string eqtext = in->getEquation()->getText(); 
            if (eqtext.empty()){
                //Criar classe para gerar o nome dos parâmetros? 
                string numerator = buildNumerator(in);
                string denominator = buildDenominator(in);
                if (denominator.empty())
                    newterm = signal + numerator; 
                else 
                    newterm = signal + numerator + "/" + denominator; 
            }
            else {
                newterm = eqtext;      
            }
            nodeEquations[idSink].push_back("+"+newterm);
            for (int src: in->getSources())
                nodeEquations[src].push_back("-"+newterm); 
            //cout << "New term: " << newterm << endl; 
        }
        /*cout << "Parameters for interaction  " << in->getId() << ":\n";
        for (pair<string,float> p: in->getEquation()->getParameters()){            
            cout << p.first << endl; 
        }*/
    }

    //Analisar para cada interação equações que estão vazias 
    for (Interaction *in: interactions){
        if (in != nullptr){
            Equation *eq = in->getEquation(); 
            if (eq != nullptr){
                vector<pair<string,float>> newparams = eq->getParameters();
                for (pair<string,float> p: newparams)
                    if (!get<0>(p).empty())
                        parameters.push_back(p);
            }
        }
    }
    /*cout << "Parameters\n"; 
    for (pair<string,float> p: parameters){
        cout << p.first << endl; 
    }*/

    if (fp.is_open()){
        fp << "vars "; 
        for (pair<string,float> p: vars){
            if (p == vars.back())
                fp << get<0>(p);
            else
                fp << get<0>(p) << ", ";
        }
        fp << endl; 
        fp << "params ";        
        for (pair<string,float> p: parameters){   
            if (p == parameters.back())
                fp << get<0>(p);
            else  
                fp << get<0>(p) << ", ";
        }        
        fp << endl;
    }

    //Gerar a inicializacao com base nos vectors 
    fp << "\nini\n"; 
    for (pair<string,float> p: vars){
        fp << get<0>(p) << " = " << get<1>(p) << endl; 
    }
    for (pair<string,float> p: parameters){
        fp << get<0>(p) << " = " << get<1>(p) << endl; 
    }        
    
    string eqname; 
    fp << "\neqs\n";
    for (pair<int,vector<string>> p: nodeEquations) {
        eqname = "d" + graph->getNode(p.first)->getName() + "_dt";
        fp << eqname << " = "; 
        equationNames.push_back(eqname);
        for (string eq: p.second)
            fp << eq << " "; 
        fp << endl; 
    }    
    fp.close(); 
    //Nome da equação = nome da interação em que ela está definida     
    //Obs: todos os termos de um nó serão inseridos no pair nodeEquations. 
    //Cada termo ocupará uma posição do vector. 
    /* Para cada interação, realizar as seguintes ações: 
        1. Verificar se o status é igual a 1. 
        2.  Verificar se mainNode está definido: 
            . Verificar direção da ligação com mainNode: 
                . fromNode: definir o sinal da equação como negativo; 
                . toNode: definir o sinal da equação como positivo; 
            . Verificar se o texto da equação está vazio. 
                . Se vazio, verificar influência positiva. 
                    . Se joinRule == AND:
                        . Concetenar um parametro e 
                        . Para cada nó em posI: 
                            . Concatenar o nome do nó com multiplicação no numerador. 
                . Se vazio, verificar influência negativa. 
                    . Se joinRule == AND:
                        . Concatenar um parametro e 
                        . Para cada nó em negI: 
                            . Concatenar o nome do nó com multiplicação no denominador. 
                . Acrescentar concat(sinal,numerador,/,denominador) em nodeEquations[mainNode]. 
                . Se não vazio, acrescentar concat(sinal,textoeq) em nodeEquations[mainNode]. 

        3. Verificar se sink está definido: 
            . Verificar se o texto da equação está vazio. 
                . Se vazio, verificar influência positiva. 
                    . Se joinRule == AND:
                        . Concetenar um parametro e 
                        . Para cada nó em posI: 
                            . Concatenar o nome do nó com multiplicação no numerador. 
                . Se vazio, verificar influência negativa. 
                    . Se joinRule == AND:
                        . Concatenar um parametro e 
                        . Para cada nó em negI: 
                            . Concatenar o nome do nó com multiplicação no denominador. 
                . Para cada source: Acrescentar concat(-,numerador,/,denominador) em nodeEquations[source]. 
                . Acrescentar concat(+,numerador,/,denominador) em nodeEquations[sink]. 
                . Se não vazio, 
                    . Para cada source: Acrescentar concat(-,eqtext) em nodeEquations[source]. 
                    . Acrescentar concat(+,eqtext) em nodeEquations[sink]. 
    */        
}

string pythonTab(int level){
    string deslocamento = "";
    while (level!=0)
    {
        level = level - 1;
        deslocamento += "    ";
    }
    return deslocamento;
}

void CodeGeneration::generateODEImports(){
    stringstream ss;
    ss << "# -*- coding: utf-8 -*-\n";    
    ss << "import numpy as np\n";
    //ss << "from scipy import integrate\n";
    ss << "from scipy.integrate import odeint";
    replaceString("$imports",ss.str());    
}

void CodeGeneration::generateODEInitialization(){
    stringstream ss; 
    for (pair<string,float> p: vars){
        ss << get<0>(p) << " = " << get<1>(p) << endl; 
    }
    for (pair<string,float> p: parameters){
        ss << get<0>(p) << " = " << get<1>(p) << endl; 
    }
    replaceString("$initialization",ss.str());    
}

void CodeGeneration::generateODEEquations(){ 
    stringstream ss;         
    string eqname; 
    int cont = 0;    
    for (pair<string,float> p: vars) {        
        if (cont == vars.size()-1)
            ss << "P[" << cont++ << "]" << endl; 
        else 
            ss << "P[" << cont++ << "], "; 
    }
    replaceString("$P",ss.str());
    ss.str("");
    for (pair<int,vector<string>> p: nodeEquations) {
        eqname = "d" + graph->getNode(p.first)->getName() + "_dt";
        ss << pythonTab(1);
        ss << eqname << " = "; 
        for (string eq: p.second)
            ss << eq << " "; 
        ss << endl; 
    }
    replaceString("$equations",ss.str());    
}

void CodeGeneration::generateODEPlotFile(){
    // 3 steps: load, create figure and plot  
    ifstream inputStream;
    inputStream.open("templates/odeplot_template.txt"); 
    ofstream plotFile; 
    plotFile.open("codes_generated/odeplot_code.py"); 
    string line; 
    while(getline(inputStream,line)){
        outputStream << line << endl; 
    }
    string plotstr = "t = getArrayFromFile(\"t.dat\")\n"; 
    for (string varName: varNames){
        plotstr += "$varName = getArrayFromFile(\"$varName.dat\")\n"; 
        plotstr += "[fig,ax] = createFigure('$varName', t, max($varName))\n";
        plotstr += "ax.plot(t,$varName,label=\"$varName\", color=colorVal)\n";
        plotstr += "color_index += 8\n";
        plotstr += "colorVal = scalarMap.to_rgba(color_index)\n";
        plotstr += "ax.legend(loc='upper right', fontsize=15)\n";
        plotstr += "ax.grid()\n";
        plotstr += "saveFig(fig,'$varName')\n"; 
        plotstr = replaceLocalString(plotstr,"$varName",varName);
        plotstr += "\n";
    }
    cout << "Plot string: " << plotstr << endl; 
    replaceString("$plots",plotstr);
    plotFile << outputStream.str();
    outputStream.str("");  
        
    inputStream.close();
    plotFile.close();
}

//Depends on function generateODEIR 
void CodeGeneration::generateODEPythonCode(){
    generateODEIR(); 
    //Files openning 
    odetemplate_filename = "templates/odetemplate.txt";
    odeoutput_filename = "codes_generated/odecode.py"; 
    inputFile.open(odetemplate_filename);
    string line; 
    while (getline(inputFile, line)){
        outputStream << line << endl; 
    }
    outputFile.open(odeoutput_filename);
    //simulation time (to be defined in the GUI)
    T = 100;      
    //TODO: Save file with time values    

    paramNames.clear();         
    for (pair<string,float> p: parameters){
        paramNames.push_back(p.first);
    }    
    replaceString("$T",to_string(T));
    replaceString("$vars",varNames);
    replaceString("$params",paramNames);
    string oderesult = "["; 
    for (string s: equationNames) {
        if (s == equationNames.back())
            oderesult += s;
        else 
            oderesult += s + ",";
    }
    oderesult += "]";     
    replaceString("$results",oderesult);    
    generateODEImports();
    generateODEInitialization();
    generateODEEquations();    
    string savestr;
    int k = 0;
    savestr += "saveTime('t.dat\', t)\n"; 
    for (string varName: varNames){
        savestr += "saveData('" + varName + ".dat', t, results, " + to_string(k) + ")\n"; 
        k++;
    }
    replaceString("$save",savestr);
    outputFile << outputStream.str();
    outputStream.str("");  

    generateODEPlotFile();
    outputStream.str("");  
    inputFile.close();
    outputFile.close(); 
}

//----------------------Gillespie----------------------------
string tab(int level){
    string deslocamento = "";
    while (level!=0)
    {
        level = level - 1;
        deslocamento += "\t";
    }
    return deslocamento;
}
//Generate the parameters initialization 
void CodeGeneration::generateG_Constants(){     
    stringstream ss;     
    ss << "double "; 
    for (pair<string,float> p: parameters){
        if (p == parameters.back())
            ss << get<0>(p) << " = " << get<1>(p) << ";" << endl; 
        else 
            ss << get<0>(p) << " = " << get<1>(p) << "," << endl; 
    }    
    replaceString("$constants",ss.str());
}

void CodeGeneration::generateGillespieCode(){
    string template_filename = "templates/gillespietemplate.txt";
    string output_filename = "codes_generated/gillespiecode.cpp"; 
    inputFile.open(template_filename);
    string line; 
    while (getline(inputFile, line)){
        outputStream << line << endl; 
    }
    outputFile.open(output_filename);     

    generateG_Constants();

    outputFile << outputStream.str();
    outputStream.str("");      
    inputFile.close();
    outputFile.close(); 
}