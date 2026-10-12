class CBinaryAsyncStream {
public:
    int m_bask; int m_fd; unsigned int m_isector; int m_cbSpooling;
    ~CBinaryAsyncStream();
    void Close();
};
CBinaryAsyncStream::~CBinaryAsyncStream() { Close(); }
