#ifndef __VIDE_BUFFER_H_
#define __VIDE_BUFFER_H_

class Buffer
{
 private:
    uint16_t* m_buffer;
    uint32_t m_length;

 public:
    Buffer();
    ~Buffer();
};

#endif

