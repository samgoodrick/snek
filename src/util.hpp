#ifndef UTIL_HPP
#define UTIL_HPP

template<typename T>
void round_to_multiple( T& input, T multiple )
{
    input -= ( input % multiple );
}    

#endif
