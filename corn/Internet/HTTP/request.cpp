#if (defined(_WIN32)  || defined(_WIN64))
#include "corn/Internet/HTTP/request_WinINet.cpp"
#else
#include "corn/Internet/HTTP/request_cURL.cpp"
#endif
