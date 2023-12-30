//
// Created by kijij on 9/8/2023.
//

#include "Node.h"

Node::Node(Node *pNext, const std::string &word, int ascii, int token) : p_next(pNext), ascii(ascii),
                                                                                           token(token), word(word) {
    this->ascii = ascii;
    this->word = word;
    this->token = token;
    p_next = nullptr;
}

unsigned int Node::getAscii() const {
    return ascii;
}

const std::string &Node::getWord() const {
    return word;
}

void Node::setAscii(unsigned int ascii) {
    Node::ascii = ascii;
}

void Node::setWord(const std::string &word) {
    Node::word = word;
}

Node::~Node(){
}

Node *Node::get_next(){
    return p_next;
}

void Node::set_next(Node *p_next_child){
    p_next = p_next_child;
}

unsigned int Node::getToken() const {
    return token;
}

void Node::setToken(unsigned int token) {
    Node::token = token;
}
