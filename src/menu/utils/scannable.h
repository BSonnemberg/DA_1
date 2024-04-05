#ifndef SCANNABLE_H
#define SCANNABLE_H

typedef unsigned char uint8_t;

class scannable {
public:
    const scannable& operator>>(uint8_t& ch) const;
    const scannable& operator>>(char& ch) const;
    const scannable& operator>>(int& ch) const;
};

// used for scan >>
extern scannable scan;

#endif
