#include "graph.h"
#include "equation.h"
#include "interaction.h"
#include "itemgraphic.h"
#include <cstdio>
#include <functional>
#include <sstream>
#include <string>

using namespace std;

int Graph::counter = 0;
ofstream Graph::logfile; 
ofstream Graph::outfile; 

using namespace std;

Graph::Graph(){    
    N0 = 50; 
    F_edge = 3; 
    this->nodes_size = N0;
    this->interactions_size = N0;
    this->edges_size = F_edge*N0;
    //Allocating space for nodes, interactions and edges 
    this->nodes.reserve(N0);
    this->interactions.reserve(N0);
    this->edges.reserve(F_edge*N0);
    this->xmlnodes = nullptr;
    this->xmlinteractions = nullptr;
    this->xmledges = nullptr;    
        
    Graph::logfile.open("logs/istool_log.dat"); 
    Graph::outfile.open("logs/istool_output.dat");    

    auto start = std::chrono::system_clock::now();    
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    std::cout << "started computation at " << std::ctime(&start_time);
    string s("system_log_");
    s += std::ctime(&start_time); 
    s += ".dat"; 
}

Graph::~Graph(){
    for (Node* n: nodes)
        delete n;
    for (Interaction* i: interactions)
        delete i;
    for (Edge* e: edges)
        delete e;    
    Graph::logfile.close();
    Graph::outfile.close(); 

    auto end = std::chrono::system_clock::now();    
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time);    
}

Node* Graph::getNode(int id){
    for (Node* n: nodes)
        if (n != nullptr)
            if (n->getId() == id)
                return n;    
    return nullptr;
}

Interaction* Graph::getInteraction(int id){
    for (Interaction* i: interactions)
        if (i != nullptr)
            if (i->getId() == id)
                return i;
    return nullptr;
}

Edge* Graph::getEdge(int id){
    for (Edge *e: edges)
        if (e != nullptr)
            if (e->getId() == id)
                return e;
    return nullptr;
}

vector<Node*> Graph::getNodes(){ return nodes; }
vector<Interaction*> Graph::getInteractions(){ return interactions; }
vector<Edge*> Graph::getEdges(){ return edges; }

bool Graph::searchEdge(int origin, int destiny){
    for (Edge *e: edges) {
        if (e != nullptr)
            if (e->getOrigin() == origin && e->getDestiny() == destiny)
                return true;
    }
    return false;
}

Node* Graph::createNode(){
    Graph::logfile << "Graph.createNode: Creating a node object with id " << Graph::counter << endl; 
    if (this->nodes.size() == this->nodes.capacity()){
        Graph::logfile << "Node vector is full. Resizing to 2 times the current capacity." << endl;
        this->nodes.resize(2*this->nodes.capacity());        
    }
    Node* newnode = new Node(Graph::counter++);    
    this->nodes.push_back(newnode);    
    this->nodes_size = this->nodes.size(); 
    return newnode; 
}

Node* Graph::createNodeWithValues(string name, string desc, int status, double inivalue){
    Graph::logfile << "Graph.createNode: Creating a node object with id " << Graph::counter << endl; 
    if (this->nodes.size() == this->nodes.capacity()){
        Graph::logfile << "Node vector is full. Resizing to 2 times the current capacity." << endl;
        this->nodes.resize(2*this->nodes.capacity());        
    }
    Node* newnode = new Node(Graph::counter++,name,desc,status,inivalue);
    this->nodes.push_back(newnode);    
    this->nodes_size = this->nodes.size(); 
    return newnode;
}

Node* Graph::createNodeWithValues(int id, string name, string desc, int status, double inivalue, ItemGraphic *g){
    Graph::logfile << "Graph.createNode: Creating a node object with id " << Graph::counter << endl; 
    if (this->nodes.size() == this->nodes.capacity()){
        Graph::logfile << "Node vector is full. Resizing to 2 times the current capacity." << endl;
        this->nodes.resize(2*this->nodes.capacity());        
    }
    Node* newnode = new Node(Graph::counter++,name,desc,status,inivalue,g);
    this->nodes.push_back(newnode);    
    this->nodes_size = this->nodes.size(); 
    return newnode;
}

//Verifica se já existe outro nó, interação ou aresta com o id dado
Node* Graph::createNodeWithValues(int id, string name, string desc, int status, double inivalue){
    Graph::logfile << "Graph.createNode: Creating a node object with id " << Graph::counter << endl; 
    if (this->nodes.size() == this->nodes.capacity()){
        Graph::logfile << "Node vector is full. Resizing to 2 times the current capacity." << endl;
        this->nodes.resize(2*this->nodes.capacity());        
    }
    Node* newnode = new Node(id,name,desc,status,inivalue);
    this->nodes.push_back(newnode);    
    this->nodes_size = this->nodes.size(); 
    return newnode;
}

Interaction* Graph::createInteraction(){
    logfile << "Graph.createInteraction: Creating an interaction object with id " << Graph::counter << endl;     
    if (this->interactions.size() == this->interactions.capacity()){
        Graph::logfile << "Interaction vector is full. Resizing to 2 times the current capacity." << endl;
        this->interactions.resize(2*this->interactions.capacity());        
    }
    Interaction* interaction = new Interaction(Graph::counter++," ");
    this->interactions.push_back(interaction);
    this->interactions_size = this->interactions.size(); 
    return interaction;
}

Interaction* Graph::createInteractionWithValues(string name, string type, int status, Equation *eq){
    logfile << "Graph.createInteraction: Creating an interaction object with id " << Graph::counter << endl;     
    if (this->interactions.size() == this->interactions.capacity()){
        Graph::logfile << "Interaction vector is full. Resizing to 2 times the current capacity." << endl;        
        this->interactions.resize(2*this->interactions.capacity());        
    }
    Interaction* interaction = new Interaction(Graph::counter++,name,type,status,eq);
    this->interactions.push_back(interaction);
    this->interactions_size = this->interactions.size(); 
    return interaction;
}

Interaction* Graph::createInteractionWithValues(string name, string type, int status, Equation *eq, 
    float p){
    Graph::logfile << "Creating an interaction object" << endl;
    if (this->interactions.size() == this->interactions.capacity()){
        Graph::logfile << "Interaction vector is full. Resizing to 2 times the current capacity." << endl;
        this->interactions.resize(2*this->interactions.capacity());        
    }
    Interaction* interaction = new Interaction(Graph::counter++,name,type,status,eq,p);
    this->interactions.push_back(interaction);
    this->interactions_size = this->interactions.size(); 
    return interaction;
}

Interaction* Graph::createInteractionWithValues(int id, string name, string type, int status, int mn, 
        vector<int> srcn, int sn, vector<int> posI, vector<int> negI, int rule, Equation *eq, float p, ItemGraphic *ig){
    Graph::logfile << "Creating an interaction object" << endl;
    if (this->interactions.size() == this->interactions.capacity()){
        Graph::logfile << "Interaction vector is full. Resizing to 2 times the current capacity." << endl;
        this->interactions.resize(2*this->interactions.capacity());        
    }
    Interaction* interaction = new Interaction(id,name,type,status,mn,srcn,sn,posI,negI,rule,eq,p,ig);
    this->interactions.push_back(interaction);
    this->interactions_size = this->interactions.size(); 
    return interaction;
}

Edge* Graph::createEdge(int origin_id, int destiny_id){
    if (this->edges.size() == this->edges.capacity()){
        Graph::logfile << "Edge vector is full. Resizing to 2 times the current capacity." << endl;
        this->edges.resize(2*this->edges.capacity());        
    }
    if (searchEdge(origin_id, destiny_id) == false){
        Graph::logfile << "Creating an edge object" << endl;
        Node* node = getNode(origin_id);
        Interaction* interact;
        if (node != nullptr){
            interact = getInteraction(destiny_id);
            if (interact != nullptr){
                int edge_id = Graph::counter;
                node->addInteraction(Node::LinkDirection::fromNode,destiny_id);
                interact->addNode(edge_id,Node::LinkDirection::fromNode,node);
                Edge* newedge = new Edge(edge_id, origin_id, destiny_id);
                edges.push_back(newedge);
                Graph::counter++;
                this->edges_size = this->edges.size(); 
                return newedge; 
            }
        }
        else {
            node = getNode(destiny_id);
            if (node != nullptr){
                interact = getInteraction(origin_id);
                if (interact != nullptr){
                    int edge_id = Graph::counter;
                    node->addInteraction(Node::LinkDirection::toNode,origin_id);
                    interact->addNode(edge_id,Node::LinkDirection::toNode,node);
                    Edge* newedge = new Edge(edge_id, origin_id, destiny_id);
                    edges.push_back(newedge);
                    Graph::counter++;
                    this->edges_size = this->edges.size(); 
                    return newedge; 
                }
            }
        }        
    }
    this->edges_size = this->edges.size(); 
    return nullptr; 
}

void Graph::editNode(int id, string name, string desc, int status, double inivalue){
    //call set methods 
    Node *n = getNode(id);
    if (n != nullptr) {
        n->setName(name); 
        n->setDesc(desc);
        n->setStatus(status);
        n->setInitialValue(inivalue);
    }     
    Graph::logfile << "O nó de id " << id << " não foi encontrado" << endl; 
}

void Graph::editInteraction(int id, string name, string type, int status, Equation *eq, float p){
    Interaction* i = getInteraction(id); 
    if (i != nullptr){
        i->setName(name);
        i->setType(type);
        i->setStatus(status); 
        i->setEquation(eq); 
        i->setProbability(p);
    }
    Graph::logfile << "A interação de id " << id << " não foi encontrada" << endl; 
}

int Graph::getNodePos(int id){
    for (int i = 0; i < nodes.size(); ++i)
        if (nodes.at(i) != nullptr)
            if (nodes.at(i)->getId() == id)
                return i;     
    return -1; 
}

int Graph::getInteractionPos(int id){
    for (int i = 0; i < interactions.size(); ++i)
        if (interactions.at(i) != nullptr)
            if (interactions.at(i)->getId() == id)
                return i;     
    return -1; 
}

/* bool Graph::hasNodeLinked(Edge* e){
}

bool Graph::hasInteractionLinked(Edge *e){
}
 */
void Graph::removeNode(int id){
    int pos = getNodePos(id);     
    int todelete = 0;
    if (pos != -1) {       
        Node *node = nodes.at(pos);
        nodes.erase(nodes.begin()+pos); 
        int esize = edges.size();         
        for (int j = 0; j < esize; j++){
            if (edges.size() == 0) break; 
            Edge *e = edges.at(j);
            if (e == nullptr) continue; 
            if (e->getOrigin() == id){ 
                cout << "removeNode: remove edge with origin" << endl; 
                edges.erase(edges.begin() + j);
                getInteraction(e->getDestiny())->removeNode(id);
                todelete = 1;                
            }
            if (e->getDestiny() == id){
                cout << "removeNode: remove edge with destiny" << endl; 
                edges.erase(edges.begin() + j);
                getInteraction(e->getOrigin())->removeNode(id);
                todelete = 2;                
            }
            if (todelete >= 1){
                delete e;                
                todelete = 0;
                j--;  
                esize--;
                if (esize == 0) break; 
            }
        }        
        delete node;        
        edges_size = edges.size();
        nodes_size = nodes.size();
    }
    else 
        Graph::logfile << "[removeNode]: O nó de id " << id << " não foi encontrado" << endl; 
}

void Graph::removeInteraction(int id){
    int todelete = 0; 
    int pos = getInteractionPos(id);
    if (pos != -1) {        
        Interaction *in = interactions.at(pos);
        interactions.erase(interactions.begin()+pos);
        int esize = edges.size(); 
        for (int j = 0; j < esize; j++){ 
            if (edges.size() == 0) break; 
            Edge *e = edges.at(j);
            if (e == nullptr) continue; 
            if (e->getOrigin() == id){
                cout << "removeInteraction: remove edge with origin" << endl; 
                edges.erase(edges.begin() + j);                
                todelete = 1;
                getNode(e->getDestiny())->removeInteraction(id);
            }
            if (e->getDestiny() == id){                
                cout << "removeInteraction: remove edge with destiny" << endl; 
                edges.erase(edges.begin() + j);                
                todelete = 2;
                getNode(e->getOrigin())->removeInteraction(id);
            }
            if (todelete >= 1){
                delete e;                
                todelete = 0;
                j--;  
                esize--;
                if (esize == 0) break; 
            }
        }                
        delete in; 
        edges_size = edges.size();
        interactions_size = interactions.size(); 
    }
    else 
        Graph::logfile << "[removeInteraction]: O nó de id " << id << " não foi encontrado" << endl; 
}

void Graph::addNode(Node *n){
    if (this->nodes.size() == this->nodes.capacity()){
        Graph::logfile << "Node vector is full. Resizing to 2 times the current capacity." << endl;        
        this->nodes.resize(2*this->nodes.capacity());        
    }
    if (n != nullptr)
        this->nodes.push_back(n);
    this->nodes_size = this->nodes.size(); 
}

void Graph::addEdge(Edge *e){
    if (this->edges.size() == this->edges.capacity()){
        Graph::logfile << "Edge vector is full. Resizing to 2 times the current capacity." << endl;        
        this->edges.resize(2*this->edges.capacity());        
    }
    if (e != nullptr)
        this->edges.push_back(e);
    this->edges_size = this->edges.size(); 
}

void Graph::printNodes(){
    for (int i = 0; i < nodes.size(); ++i) 
        if (nodes.at(i) != nullptr)
            Graph::outfile << (*nodes.at(i));
}

void Graph::printInteractions(){
    for (int i = 0; i < interactions.size(); ++i) 
        if (interactions.at(i) != nullptr)
            Graph::outfile << (*interactions.at(i));
}

void Graph::printEdges(){
    for (int i = 0; i < edges.size(); ++i) 
        if (edges.at(i) != nullptr)
            Graph::outfile << (*edges.at(i));            
}

vector<Interaction*> Graph::getInLinks(int id){
    //Verifica se é um id de um Node
    //Depois percorre a lista de interações e para cada uma verifica se id 
    //é o id de algum nó em linkedNodes. 
    vector<Interaction*> in_links; 

    return in_links; 
}

//Todo: implementar verificações de erros 
void Graph::readModelXml(string fname){
    int nNodes = this->nodes_size, nInteractions = this->interactions_size, nEdges = this->edges_size; 
    //Verifica se o grafo está vazio?
    //Create a graph representation from xml and send the graph in a signal to the canvas
    using namespace rapidxml;
    Graph::counter = 0;
    rapidxml::file<> xmlFile(fname.c_str());

    xml_document<> doc;    // character type defaults to char
    doc.parse<0>(xmlFile.data());    // 0 means default parse flags
    Graph::logfile << "Root: " << doc.first_node()->name() << "\n";
    
    //Lê as informações dos nodes 
    xml_node<> *node = doc.first_node()->first_node("nodes")->first_node(); 
    Graph::logfile << "size " << doc.first_node()->first_node("nodes")->value_size() << endl;
    xmlnodes = new nodeinfo[this->nodes_size]; 
    int count = 0;
    for (xml_node<> *n = node; n != NULL; n = n->next_sibling()){
        xmlnodes[count].id = n->first_attribute()->value();
        xml_node<> *child = n->first_node("name");
        xmlnodes[count].name = child->first_node()->value(); 
        child = child->next_sibling();
        if (child == nullptr) {
            Graph::logfile << "graphic is null" <<endl;
            //Error 
            return; 
        }
        xmlnodes[count].graphic = new graphicinfo;         
        for (xml_attribute<> *attr = child->first_attribute();
                attr; attr = attr->next_attribute()){
            if (strcmp(attr->name(),"x") == 0)
                xmlnodes[count].graphic->x = atof(attr->value());
            else if (strcmp(attr->name(),"y") == 0)
                xmlnodes[count].graphic->y = atof(attr->value());
            else if (strcmp(attr->name(),"color") == 0)
                xmlnodes[count].graphic->color = attr->value();
        }
        child = child->next_sibling();
        if (child == nullptr) {
            Graph::logfile << "status is null" <<endl;
            break;
        }
        xmlnodes[count].status = atoi(child->first_node()->value()); 
        child = child->next_sibling();
        xmlnodes[count].initial_value = atof(child->first_node()->value()); 
        count++;
        if (count == this->nodes_size) {
            xmlnodes = (nodeinfo*) realloc(xmlnodes,2*this->nodes_size*sizeof(nodeinfo));
            nNodes = 2*this->nodes_size; 
        }
    }
    
    Graph::logfile << "Nodes info:" << endl;
    for(int i = 0; i < nNodes; i++){
        if (xmlnodes[i].id.empty()) break;
        Graph::logfile << xmlnodes[i].id << endl;
        Graph::logfile << xmlnodes[i].name << endl;
        //Graph::logfile << xmlnodes[i].x << endl;
        //Graph::logfile << xmlnodes[i].y << endl;
        ItemGraphic *ig = new ItemGraphic(xmlnodes[i].graphic->x,xmlnodes[i].graphic->y,xmlnodes[i].graphic->color);
        this->createNodeWithValues(atoi(xmlnodes[i].id.c_str()),xmlnodes[i].name," ", xmlnodes[i].status, 
                xmlnodes[i].initial_value, ig);
    }

    //-------------------------------//-----------------------
    //Lê as informações das edges
    xmledges = new edgeinfo[this->edges_size];
    node = doc.first_node()->first_node("edges")->first_node();
    count = 0;
    for (xml_node<> *n = node; n != NULL; n = n->next_sibling()){
        xmledges[count].id = n->first_attribute()->value();
        Graph::logfile << "Edge id " << xmledges[count].id;
        xml_attribute<> *attr = n->first_attribute()->next_attribute();
        xmledges[count].origin_id = atoi(attr->value());
        attr = attr->next_attribute();
        xmledges[count].destiny_id = atoi(attr->value());
        attr = attr->next_attribute();
        xmledges[count].expr = attr->value();
        count++;
        if (count == this->edges_size) {
            xmledges = (edgeinfo*) realloc(xmledges,2*this->edges_size*sizeof(edgeinfo));
            nEdges = 2*this->edges_size; 
        }
    }

    Graph::logfile << "Edges info:" << endl;
    for(int i = 0; i < nEdges; i++){
        if (xmledges[i].id.empty()) break;
        Graph::logfile << xmledges[i].id << endl;
        Graph::logfile << xmledges[i].origin_id << endl;
        Graph::logfile << xmledges[i].destiny_id << endl;
        Graph::logfile << xmledges[i].expr << endl;
        Edge* newedge = new Edge(stoi(xmledges[i].id), xmledges[i].origin_id, xmledges[i].destiny_id, 
        1, xmledges[i].expr); 
        this->addEdge(newedge); 
    }

    //-------------------------------//-----------------------
    //Lê as informações das interactions 
    xmlinteractions = new interactioninfo[this->interactions_size]; 
    node = doc.first_node()->first_node("interactions")->first_node();
    count = 0;
    for (xml_node<> *n = node; n != nullptr; n = n->next_sibling()){
        xmlinteractions[count].id = n->first_attribute()->value();
        xml_node<> *child = n->first_node("name");
        if (child == nullptr){
            break; 
            //Error
        }        
        xmlinteractions[count].name = child->first_node()->value(); //get cdata
        child = child->next_sibling();  
        xmlinteractions[count].graphic = new graphicinfo;       
        for (xml_attribute<> *attr = child->first_attribute();
                attr; attr = attr->next_attribute()){
            if (strcmp(attr->name(),"x") == 0)
                xmlinteractions[count].graphic->x = atof(attr->value());
            else if (strcmp(attr->name(),"y") == 0)
                xmlinteractions[count].graphic->y = atof(attr->value());
            else if (strcmp(attr->name(),"color") == 0)
                xmlinteractions[count].graphic->color = attr->value(); 
        }        
        child = child->next_sibling();
        xmlinteractions[count].type = child->first_node()->value(); //get cdata
        //Graph::logfile << xmlinteractions[count].type << endl;        
        child = child->next_sibling();
        xmlinteractions[count].status = atoi(child->first_node()->value()); //get cdata
        xml_node<> *links = child->next_sibling();
        child = links->first_node();        
        int i = 0;
        xmlinteractions[count].max_links = nEdges; 
        xmlinteractions[count].links = new linkinfo[xmlinteractions[count].max_links]; 
        for (;child; child = child->next_sibling()){
            xmlinteractions[count].links[i].edge_id = atoi(child->first_attribute()->value());
            xmlinteractions[count].links[i].node_id = atoi(child->first_attribute()->next_attribute()->value());
            xmlinteractions[count].links[i].link_direction = child->first_attribute()->next_attribute()->next_attribute()->value();
            i++;
            if (i == xmlinteractions[count].max_links) {
                xmlinteractions[count].links = (linkinfo*) realloc(xmlinteractions[count].links, 
                                2*xmlinteractions[count].max_links*sizeof(linkinfo)); 
                xmlinteractions[count].max_links = 2*xmlinteractions[count].max_links; 
            }
        }
        xmlinteractions[count].num_of_links = i;
        xml_node<> *relations = links->next_sibling();
        cout << relations->name() << endl;
        xml_node<> *mainnode = relations->first_node();
        cout << mainnode->name() << endl;
        xml_attribute<> *attr = mainnode->first_attribute();
        if (attr != nullptr) {
            cout << "mainnode id " <<  attr->value() << endl;
            xmlinteractions[count].mainNode = atoi(attr->value());
        }
        else  
            xmlinteractions[count].mainNode = -1; 
        xml_node<> *sources = mainnode->next_sibling();         
        xml_node<> *source = sources->first_node(); //get first source child          
        for (;source; source = source->next_sibling()){
            attr = source->first_attribute();
            cout << "source id " <<  attr->value() << endl; 
            xmlinteractions[count].sourceNodes.push_back(atoi(attr->value()));
        }
        xml_node<> *sink = sources->next_sibling();
        attr = sink->first_attribute();            
        if (attr != nullptr)
            xmlinteractions[count].sinkNode = atoi(attr->value());
        else 
            xmlinteractions[count].sinkNode = -1; 
        cout << "Pos influence" << endl; 
        xml_node<> *posInfluence = sink->next_sibling();
        if (posInfluence != nullptr){ 
            child = posInfluence->first_node();
            //cout << child->name() << endl;
            for (;child; child = child->next_sibling()){
                attr = child->first_attribute();
                if (attr != nullptr)
                    xmlinteractions[count].positiveInfluences.push_back(atoi(attr->value()));
            }
        }
        xml_node<> *negInfluence = posInfluence->next_sibling();        
        if (negInfluence != nullptr){
            child = negInfluence->first_node(); 
            for (;child; child = child->next_sibling()){
                xml_attribute<> *attr = child->first_attribute();
                if (attr != nullptr)
                    xmlinteractions[count].negativeInfluences.push_back(atoi(attr->value()));
            }
        }
        xml_node<> *join_rule = negInfluence->next_sibling();
        attr = join_rule->first_attribute();
        if (attr != nullptr) {
            if (strcmp(attr->value(),"and") == 0)
                xmlinteractions[count].joinRule = 0;
            else 
                xmlinteractions[count].joinRule = 1;
        }

        xmlinteractions[count].equation = nullptr;     
        xml_node<> *equation = n->first_node("equation");
        if (equation != nullptr && equation->first_node() != nullptr) {
            cout << "Equation is not null" << endl;
            xmlinteractions[count].equation = new equationinfo; 
            xml_node<> *parameters = equation->first_node();
            child = parameters->first_node(); 
            string name; 
            float value; 
            for (;child; child = child->next_sibling()){
                attr = child->first_attribute();
                if (attr != nullptr)    
                    name = attr->value(); 
                attr = attr->next_attribute();
                if (attr != nullptr)   
                    value = atof(attr->value()); 
                xmlinteractions[count].equation->parameters.push_back(make_pair(name,value));
            }
            xml_node<> *vars = parameters->next_sibling();
            child = vars->first_node();         
            for (;child; child = child->next_sibling()){
                attr = child->first_attribute();
                if (attr != nullptr)    
                    xmlinteractions[count].equation->node_ids.push_back(atoi(attr->value()));
            } 
            xml_node<> *text = vars->next_sibling();            
            xmlinteractions[count].equation->text = text->first_node()->value();            
            cout << "Eq text " << xmlinteractions[count].equation->text << endl; 
        }
        xml_node<> *probability = relations->next_sibling("probability");
        attr = probability->first_attribute();
        if (attr != nullptr)
            xmlinteractions[count].p = atof(attr->value());
        else 
            xmlinteractions[count].p = 1; 

        count++;
        if (count == this->interactions_size) {
            xmlinteractions = (interactioninfo*) realloc(xmlinteractions,2*this->interactions_size*sizeof(interactioninfo));
            nInteractions = 2*this->interactions_size; 
        }
    }

    Graph::logfile << "Interactions info:" << endl;
    for(int i = 0; i < nInteractions; i++){
        if (xmlinteractions[i].id.empty()) break;
        Graph::logfile << xmlinteractions[i].id << endl;
        Graph::logfile << xmlinteractions[i].name << endl;
        Graph::logfile << xmlinteractions[i].type << endl;
        Graph::logfile << "Links: " << endl;
        for(int j = 0; j < xmlinteractions[i].num_of_links; j++){
            Graph::logfile << "edgeid " << xmlinteractions[i].links[j].edge_id << endl;
            Graph::logfile << "nodeid " << xmlinteractions[i].links[j].node_id << endl;
            Graph::logfile << "link direction " << xmlinteractions[i].links[j].link_direction << endl; 
        }
        Graph::logfile << "Relations:" << endl;
        Graph::logfile << "mainnode = " << xmlinteractions[i].mainNode << endl;        
        Graph::logfile << "sources:\n"; 
        for(int s: xmlinteractions[i].sourceNodes){
            Graph::logfile << " " << s << ",\n";
        }
        Graph::logfile << "sink = " << xmlinteractions[i].sinkNode << "\n"; 
        Graph::logfile << "positive influences:\n"; 
        for(int s: xmlinteractions[i].positiveInfluences){
            Graph::logfile << " " << s << ",\n";
        }
        Graph::logfile << "negative influences:\n"; 
        for(int s: xmlinteractions[i].negativeInfluences){
            Graph::logfile << " " << s << ",\n";
        }
        Graph::logfile << "join_rule = " << xmlinteractions[i].joinRule << "\n"; 
        Equation *neweq = new Equation(); 
        if (xmlinteractions[i].equation != nullptr){
            Graph::logfile << "parameters:\n"; 
            for(pair<string,float> p: xmlinteractions[i].equation->parameters){
                Graph::logfile << " (name =  " << p.first << ", value = " << p.second << ")\n";
            }
            Graph::logfile << "vars:\n"; 
            for(int id: xmlinteractions[i].equation->node_ids){
                Graph::logfile << " " << id << "\n";
            }
            Graph::logfile << "text = " << xmlinteractions[i].equation->text << "\n"; 
            
            neweq = new Equation(xmlinteractions[i].equation->parameters, 
                xmlinteractions[i].equation->node_ids, xmlinteractions[i].equation->text);  
        }
        Graph::logfile << "probability = " << xmlinteractions[i].p << "\n";        

        ItemGraphic *ig = new ItemGraphic(xmlinteractions[i].graphic->x,xmlinteractions[i].graphic->y,xmlinteractions[i].graphic->color);

        Interaction* newInteraction = this->createInteractionWithValues(atoi(xmlinteractions[i].id.c_str()),
            xmlinteractions[i].name, xmlinteractions[i].type, xmlinteractions[i].status, xmlinteractions[i].mainNode,
            xmlinteractions[i].sourceNodes, xmlinteractions[i].sinkNode, xmlinteractions[i].positiveInfluences,
            xmlinteractions[i].negativeInfluences, xmlinteractions[i].joinRule, neweq, xmlinteractions[i].p, ig);  
        //Inserir os nodes dos links em newInteraction
        for(int j = 0; j < xmlinteractions[i].num_of_links; j++){
            Node *ntemp = getNode(xmlinteractions[i].links[j].node_id);
            if (ntemp == nullptr) break; 
            if (xmlinteractions[i].links[j].link_direction.compare("fromNode") == 0) { 
                ntemp->addInteraction(Node::LinkDirection::fromNode, newInteraction->getId()); 
                newInteraction->addNode(xmlinteractions[i].links[j].edge_id, Node::LinkDirection::fromNode, ntemp); 
            }
            else if (xmlinteractions[i].links[j].link_direction.compare("toNode") == 0) {
                ntemp->addInteraction(Node::LinkDirection::toNode, newInteraction->getId()); 
                newInteraction->addNode(xmlinteractions[i].links[j].edge_id, Node::LinkDirection::toNode, ntemp); 
            }
        } 
    }

    Graph::logfile << "Finished reading xml";
    doc.clear();

    delete[] xmlnodes;     
    for(int i = 0; i < nInteractions; i++) {
        if (xmlinteractions[i].id.empty()) break;
        delete xmlinteractions[i].equation; 
    }
    delete[] xmlinteractions;
    delete[] xmledges;
}

//Colocar um identificador único em todos os nós do xml?
void Graph::saveGraphToXml(string fname){
    /*Percorre a lista de nós salvandos os nós e seus atributos dentro de nodes
    */ 
    using namespace rapidxml; 
    // Write xml file =================================    
    xml_document<> doc;
    xml_node<>* decl = doc.allocate_node(node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(decl);

    xml_node<>* root = doc.allocate_node(node_element, "model");
    doc.append_node(root);
/*
        <links>
          <link edge_id="3" node_id="0" direction="fromNode"/>
          <link edge_id="4" node_id="1" direction="toNode"/>
          <link edge_id="6" node_id="5" direction="fromNode"/>
        </links>
        <relations>    
          <mainnode id="0"/>       
          <sources>
            <source id="0"/>
            <source id="1"/>
          </sources>
          <sink id="1"/>
          <positive_influences> 
            <node id="0"/>
            <node id="1"/>
          </positive_influences>
          <negative_influences> 
            <node id="0"/>
          </negative_influences>
          <join_rule value="and"/>
        </relations>
        <equation>
            <parameters>
                <parameter name="k_b_n" value="0.1"/>                
            </parameters>
            <vars>
                <var id="0"/>
                <var id="1"/>
            </vars>
            <text>
                <![CDATA[k_b_n*B*N]]>
            </text>
        </equation>
        <probability value="0.8"/> 
      </interaction>
*/

    xml_node<>* child_nodes = doc.allocate_node(node_element, "nodes");
    root->append_node(child_nodes);
    for (Node *n: nodes){
        if (n != nullptr){
            xml_node<>* node = doc.allocate_node(node_element, "node");
            //string s(n->getId());            
            node->append_attribute(doc.allocate_attribute("id",doc.allocate_string(to_string(n->getId()).c_str())));
            xml_node<>* nodetemp = doc.allocate_node(node_element, "name");
            nodetemp->append_node(doc.allocate_node(node_cdata,
                "", doc.allocate_string(n->getName().c_str())));
            node->append_node(nodetemp);
            nodetemp = doc.allocate_node(node_element, "graphic");
            if (n->getItemGraphic() != nullptr) {
                nodetemp->append_attribute(doc.allocate_attribute("x",doc.allocate_string(to_string(n->getItemGraphic()->getX()).c_str())));
                nodetemp->append_attribute(doc.allocate_attribute("y",doc.allocate_string(to_string(n->getItemGraphic()->getY()).c_str())));
                nodetemp->append_attribute(doc.allocate_attribute("color",doc.allocate_string(n->getItemGraphic()->getColor().c_str())));
            }            
            node->append_node(nodetemp);
            nodetemp = doc.allocate_node(node_element, "status");
            nodetemp->append_node(doc.allocate_node(node_cdata,
                "", doc.allocate_string(to_string(n->getStatus()).c_str())));
            node->append_node(nodetemp);
            nodetemp = doc.allocate_node(node_element, "initial_value");
            nodetemp->append_node(doc.allocate_node(node_cdata,
                "", doc.allocate_string(to_string(n->getInitialValue()).c_str())));
            node->append_node(nodetemp);            
            child_nodes->append_node(node);
        }
    }

    child_nodes = doc.allocate_node(node_element, "interactions");
    root->append_node(child_nodes);
    for (Interaction *in: interactions){
        if (in != nullptr){
            xml_node<>* internode = doc.allocate_node(node_element, "interaction");
            xml_node<>* nodetemp = doc.allocate_node(node_element, "name");
            nodetemp->append_node(doc.allocate_node(node_cdata,
                "", doc.allocate_string(in->getName().c_str())));
            internode->append_node(nodetemp);

            nodetemp = doc.allocate_node(node_element, "graphic");
            if (in->getItemGraphic() != nullptr) {
                nodetemp->append_attribute(doc.allocate_attribute("x",doc.allocate_string(to_string(in->getItemGraphic()->getX()).c_str())));
                nodetemp->append_attribute(doc.allocate_attribute("y",doc.allocate_string(to_string(in->getItemGraphic()->getY()).c_str())));
                nodetemp->append_attribute(doc.allocate_attribute("color",doc.allocate_string(in->getItemGraphic()->getColor().c_str())));
            }  
            internode->append_node(nodetemp);
            //type, status, links, relations  
            nodetemp = doc.allocate_node(node_element, "type");
            nodetemp->append_node(doc.allocate_node(node_cdata,
                "", doc.allocate_string(in->getType().c_str())));
            internode->append_node(nodetemp);
            nodetemp = doc.allocate_node(node_element, "status");
            nodetemp->append_node(doc.allocate_node(node_cdata,
                "", doc.allocate_string(to_string(in->getStatus()).c_str())));
            internode->append_node(nodetemp);

            nodetemp = doc.allocate_node(node_element, "links");

            child_nodes->append_node(internode);
        }
    }

    // Convert doc to string if needed
    //std::string xml_as_string;
    //rapidxml::print(std::back_inserter(xml_as_string), doc);
    // Save to file
    std::ofstream file_stored(fname);
    file_stored << doc;
    file_stored.close();
    doc.clear();
}
