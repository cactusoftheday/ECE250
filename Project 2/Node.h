//
// Created by kijij on 9/8/2023.
//

#include <string>
class Node {
    public:

    Node(Node *pNext, const std::string &word, int ascii, int token);

    ~Node();

    Node *get_next();

    void set_next(Node *p_next_child);

    unsigned int getAscii() const;

    const std::string &getWord() const;

    unsigned int getToken() const;

    void setToken(unsigned int token);

    void setAscii(unsigned int ascii);

    void setWord(const std::string &word);

    Node *p_next; //ran into problems making this private
    private:
        unsigned int ascii;
        unsigned int token;
        std::string word;
};

