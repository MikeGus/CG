#ifndef SIGN_H
#define SIGN_H

template <typename T>
int get_sign(T x)
{
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

#endif // SIGN_H
