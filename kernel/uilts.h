//can be faster
void memory_copy(char *source, char *dest, int nbytes);


// ports
inline unsigned char port_byte_in (unsigned short port);
inline void port_byte_out (unsigned short port, unsigned char data);

inline unsigned short port_word_in (unsigned short port);
inline void port_word_out (unsigned short port, unsigned short data);

typedef unsigned    char u8;
typedef             char s8;
typedef unsigned    short u16;
typedef             short s16;
