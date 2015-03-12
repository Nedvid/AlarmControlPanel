#ifndef DEBUG_HPP
    #ifdef DEBUG
        #include <cstdio>
        
        #define debug(format, ...)     std::printf(format,##__VA_ARGS__)
        
        /*
         * Disable STDOUT buffering to enable printing before a newline 
         * character or buffer flush.
         */
        std::setbuf(stdout, NULL);
    #else
        #define debug(format, ...)
    #endif /* DEBUG */
#endif /* DEBUG_HPP */