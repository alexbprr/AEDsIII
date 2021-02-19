#include <iostream>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include <cstring>

using namespace std; 
/*    Because all RapidXml interface is contained inside namespace rapidxml, users must either 
    bring contents of this namespace into scope, or fully qualify all the names. 
    Class xml_document represents a root of the DOM hierarchy. By means of public inheritance, 
    it is also an xml_node and a memory_pool. Template parameter of xml_document::parse() 
    function is used to specify parsing flags, with which you can fine-tune behaviour of the 
    parser. Note that flags must be a compile-time constant.*/

typedef struct TNodeInfo {
    string id; 
    string name; 
    float x;
    float y; 
} nodeinfo;

typedef struct TLinkInfo {
    int edge_id;
    int node_id;
}linkinfo;

typedef struct TInteractionInfo {
    string id; 
    string name; 
    string type; 
    linkinfo links[100]; 
    int num_of_links;
    float x;
    float y; 
} interactioninfo;

int main(){
    using namespace rapidxml;
    rapidxml::file<> xmlFile("model1.xml"); 
    xml_document<> doc;    // character type defaults to char
    doc.parse<0>(xmlFile.data());    // 0 means default parse flags
    cout << "Root: " << doc.first_node()->name() << "\n";
    xml_node<> *node = doc.first_node()->first_node("nodes")->first_node(); //retorna o primeiro filho de nodes    

    cout << "size " << doc.first_node()->first_node("nodes")->value_size() << endl;
    nodeinfo* xmlnodes = (nodeinfo*) malloc(100*sizeof(nodeinfo));

    int count = 0; 
    for (xml_node<> *n = node; n != NULL; n = n->next_sibling()){        
        xmlnodes[count].id = n->first_attribute()->value();           
        xml_node<> *child = n->first_node("name");
        xmlnodes[count].name = child->first_node()->value();
        xml_node<> *graphic = child->first_node()->next_sibling();
        if (graphic == NULL) {
            cout << "graphic is null" <<endl;
            break;
        }
        for (xml_attribute<> *attr = graphic->first_attribute();
                attr; attr = attr->next_attribute()){
            if (strcmp(attr->name(),"x") == 0)
                xmlnodes[count].x = atof(attr->value());
            else if (strcmp(attr->name(),"y") == 0)
                xmlnodes[count].y = atof(attr->value());
        }         
        count++;
        if (count == 100)            
            xmlnodes = (nodeinfo*) realloc(xmlnodes,500*sizeof(nodeinfo));
    }

    cout << "Nodes info:" << endl;
    for(int i = 0; i < 100; i++){
        if (xmlnodes[i].id == "") break;
        cout << xmlnodes[i].id << endl;
        cout << xmlnodes[i].name << endl;
        cout << xmlnodes[i].x << endl;
        cout << xmlnodes[i].y << endl;
    }
    
    interactioninfo* xmlinteractions = (interactioninfo*) malloc(100*sizeof(interactioninfo));
    node = doc.first_node()->first_node("interactions")->first_node();    
    count = 0;
    for (xml_node<> *n = node; n != NULL; n = n->next_sibling()){    
        xmlinteractions[count].id = n->first_attribute()->value();           
        xml_node<> *child = n->first_node("name");
        xmlinteractions[count].name = child->first_node()->value();
        xml_node<> *graphic = child->first_node()->next_sibling();
        if (graphic == NULL) {
            cout << "graphic is null" <<endl;
            break;
        }
        for (xml_attribute<> *attr = graphic->first_attribute();
                attr; attr = attr->next_attribute()){
            if (strcmp(attr->name(),"x") == 0)
                xmlinteractions[count].x = atof(attr->value());
            else if (strcmp(attr->name(),"y") == 0)
                xmlinteractions[count].y = atof(attr->value());
        } 
        child = n->first_node("type");
        xmlinteractions[count].type = child->first_node()->value();

        child = n->first_node("links")->first_node();
        int i = 0;
        for (;child; child = child->next_sibling()){
            xmlinteractions[count].links[i].edge_id = atoi(child->first_attribute()->value());
            xmlinteractions[count].links[i].node_id = atoi(child->first_attribute()->next_attribute()->value());
            i++;
        }
        xmlinteractions[count].num_of_links = i;
        count++;        
        if (count == 100)            
            xmlinteractions = (interactioninfo*) realloc(xmlinteractions,500*sizeof(interactioninfo));
    }
    
    cout << "Interactions info:" << endl;
    for(int i = 0; i < 100; i++){
        if (xmlinteractions[i].id == "") break;
        cout << xmlinteractions[i].id << endl;
        cout << xmlinteractions[i].name << endl;
        cout << xmlinteractions[i].x << endl;
        cout << xmlinteractions[i].y << endl;
        cout << xmlinteractions[i].type << endl;
        cout << "Links: " << endl;
        for(int j = 0; j < xmlinteractions[i].num_of_links; j++){
            cout << "edgeid " << xmlinteractions[i].links[j].edge_id << endl;
            cout << "nodeid " << xmlinteractions[i].links[j].node_id << endl;
        }
    }

    free(xmlnodes);
    free(xmlinteractions);
    return 0; 
}