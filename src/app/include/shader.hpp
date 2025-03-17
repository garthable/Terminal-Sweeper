#include <cstdint>

namespace sha
{

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use();

private:
    uint32_t m_Id;
};

}