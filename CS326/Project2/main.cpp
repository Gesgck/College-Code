/*
    Name: Alec Zheng, NSHE_ID_2001982564, 1002, ASSIGNMENT_2
    Description: Scanner and Parser for esoteric language
    Input: language file
    Output: parsed language
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// LEXER ---------------------------------------------------
#define MAX_SIZE 32
#define printToken(tok) \
    printf("[Terminal:<%s='%s',line=%d>]\n", \
    names[(tok).kind], \
    symbols[(tok).kind], \
    (tok).line)

// Lexemes contained in each group of tokens.
const char* symbols[] = {
    "invalid",
    "eof", "waaaah",
    "=", "|", "#", "\"", ")", "(",
    "+", "-", ".", ":", ",", ";",
    ">", "<", "^", "!", "[", "@"
};

// Textual representation for each group of tokens.
const char* names[] = {
    "INVALID",
    "EOF", "BABY-CRY",
    "EQUAL", "BAR", "NUMERAL", "QUOTE", "PARENL", "PARENR",
    "PLUS", "MINUS", "DOT", "COLON", "COMMA", "SEMI",
    "GT", "LT", "XOR", "NOT", "BRACKL", "AT"
};

// Numerical representation for each group of tokens.
typedef enum {
    TOK_INVALID,
    TOK_END,
    TOK_BABY_CRY,       // waaaah
    TOK_EQUAL,          // =
    TOK_BAR,            // |
    TOK_NUMERAL,        // #
    TOK_QUOTE,          // "
    TOK_PARENL,         // (
    TOK_PARENR,         // ) 
    TOK_PLUS,           // +
    TOK_MINUS,          // -
    TOK_DOT,            // .
    TOK_COLON,          // :
    TOK_COMMA,          // ,
    TOK_SEMI,           // ;
    TOK_GT,             // >
    TOK_LT,             // <
    TOK_XOR,            // ^
    TOK_NOT,            // !
    TOK_BRACKL,         // [
    TOK_AT              // @
} TokenType;

// Definition of a Lexer type.
typedef struct {
    int current;        // the current character
    int line;           // the line number where the lexeme appeared
    long bufferSize;// the number of characters store in the buffer
    char* buffer;       // a dynamic array of characters
} Lexer;

// Definition of a Token type.
typedef struct {
    TokenType kind;     // type of token
    int line;           // the line number where the lexeme appeared
} Token;

/// @brief Attempts to reallocate memory on the heap based on the
/// pointer ptr. If ptr is null, a new block of memory of the specified
/// size is allocated.
/// @param ptr A previously allocated memory block, or null if new memory
/// allocation is required.
/// @param size the number of bytes to allocate.
/// @return A  newly allocated memory block if ptr is null, 
//or an existing
/// memory block pointed to by ptr with an additional size bytes 
//if ptr is
/// not null.
void *myAlloc(void *ptr, size_t size) {
    ptr = realloc(ptr, size);
    if (!ptr) {
        fprintf(stdout, "Realloc failed to allocated memory.\n");
        return 0;
    }
    return ptr;
}

/// @brief Opens and reads the entire file and stores the text in a
/// buffer array.
/// @param filename The file to opend.
/// @param lex The scanner.
void readFile(const char *filename, Lexer* lex) {
    // Open file to read
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stdout, "Failed to open file '%s'", filename);
        return;
    }
    // Compute the number of bytes needed to allocate dynamic
    // memory for the stream buffer
    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = (char*) myAlloc(NULL, sizeof(char) * (len + 1));
    if (!buffer) {
        fprintf(stdout, "Unable to allocate memory for buffer\n");
        fclose(file);
        return;
    }
    fread(buffer, 1, len, file);
    fclose(file);
    // Buffer contains the entire input 
    //so null-terminate it
    buffer[len] = '\0';
    lex->buffer = buffer;
    lex->bufferSize = len;
}

/// @brief Reads an entire line of characters not 
//including the line-feed.
/// @param[in] str the buffer array where characters are to be stored.
/// @param[in] n the maximum number of characters allowed in the buffer.
/// @return The function returns the number of characters read.
int readline(char str[], int n) {
    int ch = 0, i = 0;
    while ((ch = getchar()) != '\n') if (i < n) str[i++] = ch;
    str[i] = '\0';
    return i;
}

/// @brief Returns true if the character is a letter or an underscore.
/// @param c The character to be checked.
/// @return True if the character is a letter or an underscore, or
/// false otherwise.
bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

/// @brief Creates and returns a token from the specified type.
/// @param lex The scanner.
/// @param kind The type of token to be created.
/// @return A token of type kind.
Token makeToken(Lexer* lex, TokenType kind) {
    // TODO: your code goes here!
    return (Token){.kind = kind, .line = lex->line};
}

void consume(Lexer* lex) {
    //move current to next but dont go past the limit
    lex->current++;
    if(lex->current > lex->bufferSize)
        lex->current = lex->bufferSize;
    return;
}

void skipWhitespace(Lexer* lex) {
    //Skip all non tokens
    while(lex->buffer[lex->current] == ' ' 
    | lex->buffer[lex->current] == '\t' 
    | lex->buffer[lex->current] == '\n'){
        //increments the line for linefeed
        if(lex->buffer[lex->current] == '\n')
            lex->line++;
        consume(lex);
    }
    return;
}

bool isBabyMarioCrying(Lexer *lex) {
    char ch = lex->buffer[lex->current];
    while (isAlpha(ch)) {
        consume(lex);
        ch = lex->buffer[lex->current];
    }
    return strncmp(lex->buffer + (lex->current - 6),
     (char *)"waaaah", 6) == 0;
}

Token nextToken(Lexer* lex) {
    skipWhitespace(lex);
    if (lex->current >= lex->bufferSize) {
        // This returns the end-of-file marker. Note that we create a
        // struct 'on the fly', which is created again when we return
        // to the caller. I know...I know...not efficient but useful ;-)
        return (Token){.kind = TOK_END, .line = -1};
    }

    //table for what to return
    if(lex->buffer[lex->current] == '='){
        consume(lex);
        return makeToken(lex,TOK_EQUAL);
    }else if(lex->buffer[lex->current] == '|'){
        consume(lex);
        return makeToken(lex,TOK_BAR);
    }else if(lex->buffer[lex->current] == '#'){
        consume(lex);
        return makeToken(lex,TOK_NUMERAL);
    }else if(lex->buffer[lex->current] == '\"'){
        consume(lex);
        return makeToken(lex,TOK_QUOTE);
    }else if(lex->buffer[lex->current] == '('){
        consume(lex);
        return makeToken(lex,TOK_PARENR);
    }else if(lex->buffer[lex->current] == ')'){
        consume(lex);
        return makeToken(lex,TOK_PARENL);
    }else if(lex->buffer[lex->current] == '+'){
        consume(lex);
        return makeToken(lex,TOK_PLUS);
    }else if(lex->buffer[lex->current] == '-'){
        consume(lex);
        return makeToken(lex,TOK_MINUS);
    }else if(lex->buffer[lex->current] == '.'){
        consume(lex);
        return makeToken(lex,TOK_DOT);
    }else if(lex->buffer[lex->current] == ':'){
        consume(lex);
        return makeToken(lex,TOK_COLON);
    }else if(lex->buffer[lex->current] == ','){
        consume(lex);
        return makeToken(lex,TOK_COMMA);
    }else if(lex->buffer[lex->current] == ';'){
        consume(lex);
        return makeToken(lex,TOK_SEMI);
    }else if(lex->buffer[lex->current] == '>'){
        consume(lex);
        return makeToken(lex,TOK_GT);
    }else if(lex->buffer[lex->current] == '<'){
        consume(lex);
        return makeToken(lex,TOK_LT);
    }else if(lex->buffer[lex->current] == '^'){
        consume(lex);
        return makeToken(lex,TOK_XOR);
    }else if(lex->buffer[lex->current] == '!'){
        consume(lex);
        return makeToken(lex,TOK_NOT);
    }else if(lex->buffer[lex->current] == '['){
        consume(lex);
        return makeToken(lex,TOK_BRACKL);
    }else if(lex->buffer[lex->current] == '@'){
        consume(lex);
        return makeToken(lex,TOK_AT);
    }else if(isBabyMarioCrying(lex)){
        //if it is the beginging of the file dont skip the rest
        if(lex->line == 1){
            return makeToken(lex,TOK_BABY_CRY);
        }
        //eof, get current to the end of buffer
        while(lex->current < lex->bufferSize){
            consume(lex);
        }
        return makeToken(lex,TOK_BABY_CRY);
    }

    //If no symbols match it is invalid
    consume(lex);
    return (Token){.kind = TOK_INVALID, .line = lex->line};
}

// Initialize the scanner with some default values: current is set to 0,
// line is set to 1, buffer is set to NULL, and bufferSize is set to 0.
void initLexer(Lexer* lex) {
    lex->current = 0;
    lex->line = 1;
    lex->buffer = NULL;
    lex->bufferSize = 0;
}

// PARSER ---------------------------------------------------
// Definition of a Parser
typedef struct {
    Token* input;           // from where do we get the tokens
    int inputSize;          // the number of tokens
    TokenType lookahead;    // the current lookahead token
    int pos;                // the current position
} Parser;

void parserConsume(Parser* parser) {
    if (parser->pos > parser->inputSize - 1) parser->lookahead = TOK_END;
    else parser->lookahead = parser->input[parser->pos].kind;
    parser->pos++;
}

void initParser(Parser* parser, Token* input, int inputSize) {
    //init all values of the parser
    parser->input = input;
    parser->inputSize = inputSize;
    parser->pos = 0;
    parserConsume(parser);
}

TokenType peek(Parser* parser, int index) {
    if (parser->pos + index - 1 >= parser->inputSize)
        return parser->input[parser->pos - 1].kind;
    return parser->input[parser->pos + index - 1].kind;
}

void parserMatch(Parser* parser, TokenType type) {
    if (parser->lookahead == type) parserConsume(parser);
    else {
        fprintf(stdout, "ERROR: Invalid token!\n");
    }
}

void startProgram(Parser* parser) {
    //assume that a Baby Mario file starts 
    //and ends with the word “waaaah”
    parserConsume(parser);
}

void endProgram(Parser* parser) {
    //check for baby mario
    if(parser->lookahead != TOK_BABY_CRY)
        fprintf (stdout, "ERROR: expecting TOK_BABY_CRY!\n");
    parserConsume(parser);
}

void code(Parser* parser) {
    // Parser looks for symbols
    // and tries to match them
    while(parser->pos < parser->inputSize - 1){
        if(parser->lookahead == 3)              
            parserMatch(parser,TOK_EQUAL);
        else if(parser->lookahead == 4)
            parserMatch(parser,TOK_BAR);
        else if(parser->lookahead == 5)
            parserMatch(parser,TOK_NUMERAL);
        else if(parser->lookahead == 6)
            parserMatch(parser,TOK_QUOTE);
        else if(parser->lookahead == 7)
            parserMatch(parser,TOK_PARENL);
        else if(parser->lookahead == 8)
            parserMatch(parser,TOK_PARENR);
        else if(parser->lookahead == 9)
            parserMatch(parser,TOK_PLUS);
        else if(parser->lookahead == 10)
            parserMatch(parser,TOK_MINUS);
        else if(parser->lookahead == 11)
            parserMatch(parser,TOK_DOT);
        else if(parser->lookahead == 12)
            parserMatch(parser,TOK_COLON);
        else if(parser->lookahead == 13)
            parserMatch(parser,TOK_COMMA);
        else if(parser->lookahead == 14)
            parserMatch(parser,TOK_SEMI);
        else if(parser->lookahead == 15)
            parserMatch(parser,TOK_GT);
        else if(parser->lookahead == 16)
            parserMatch(parser,TOK_LT);
        else if(parser->lookahead == 17)
            parserMatch(parser,TOK_XOR);
        else if(parser->lookahead == 18)
            parserMatch(parser,TOK_NOT);
        else if(parser->lookahead == 19)
            parserMatch(parser,TOK_BRACKL);
        else if(parser->lookahead == 20)
            parserMatch(parser,TOK_AT);
        else if(parser->lookahead == 0){
            parserMatch(parser,TOK_INVALID);
            break;
        }
            
    }
}

void parseGoal(Parser* parser) {
    // parseGoal => start code end
    startProgram(parser);
    code(parser);
    endProgram(parser);

    if (parser->lookahead != TOK_END) {
        fprintf(stdout, "ERROR: expecting end of file token!\n");
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
    fprintf(stdout,"ERROR: invalid number of command line arguments!\n");
        return 0;
    }
    // Allocate memory for a dynamic array of tokens.
    Token* input = (Token*) myAlloc(NULL, sizeof(Token) * MAX_SIZE);
    // Maximum size of tokens allowed in the dynamic array. Note
    // that this size is increased right before the last cell
    // of the dynamic array is used.
    int maxSize = MAX_SIZE;
    // Current number of elements stored in the dynamic array.
    int count = 0;
    // Initialize the attributes of the scanner.
    Lexer lex;
    initLexer(&lex);
    // Allocate memory for the buffer array. This will contain
    // characters read from the input file.
    readFile(argv[1], &lex);
    Token token;
    do {
        token = nextToken(&lex);
        printToken(token);
        // Add a token to the dynamic array and increase the size by 1.
        input[count++] = token;
        // Dynamically resize the dynamic array...no pun intended ;-)
        // I know...Iknow...I should have doubled the size instead
        if (count >= maxSize - 1)
            input = (Token*) myAlloc(input, sizeof(Token) 
            * (maxSize += MAX_SIZE));
    } while(token.kind != TOK_END);
    // Note that this will call the start symbol, and if
    // something goes wrong as we call each rule, then we
    // should stop generating sentences.
    printf("Begining parsing...\n");
    Parser parser;
    initParser(&parser, input, count);
    parseGoal(&parser);
    printf("Done parsing!\n");
    printf("Deallocating memory...\n");
    // Deallocate dynamically allocated memory.
    free(lex.buffer);
    free(parser.input);
    printf("Done!");
    return 0;
}