#include "CGLInfo.h"
#define MAXGLERRORS 20

/**
 * Print OpenGL & GLSL Verion
 */

void SciIllLib::CGLInfo::Version()
{
	std::cout << "OpenGL Version Info:" << std::endl;
	std::cout << "> GL   " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

/**
 * Check for OpenGL errors without a specific msg
 * @returns if an error has occured
 */

bool SciIllLib::CGLInfo::CheckError()
{
	return CheckError("");
}

/**
 * Check for OpenGL errors and print out an additional msg (e.g. location)
 * @param msg A string that is printed in front of the error
 * @returns if an error has occured
 */
bool SciIllLib::CGLInfo::CheckError(const char* msg)
{
    int counter = 0;
	GLenum errCode = glGetError();
	bool result = false;
	int idx = 0;
    while (errCode != GL_NO_ERROR)
    {
        result = true;
		std::cout << "!!! OpenGLError (" << idx << "): ";
        switch (errCode)
        {
		//1280
			case GL_INVALID_ENUM:
                std::cout << "Invalid enum";
                break;
        //1281
            case GL_INVALID_VALUE:
                std::cout << "Invalid value";
                break;
        //1282
            case GL_INVALID_OPERATION:
                std::cout << "Invalid operation";
                break;
        //1280
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cout << "Invalid framebuffer operation";
                break;
            case GL_OUT_OF_MEMORY:
                std::cout << "Out of memory";
                break;
        }
        std::cout << " (" << msg << ")" << std::endl;
        errCode = glGetError();
		if (++counter > MAXGLERRORS)
			errCode = GL_NO_ERROR;
		idx++;
	}
	return result;
}

/**
 * Check for a correct FBO, as OpenGL doesnt integrate them into the usual OpenGLError mechanism
 * @returns if an error has occured
 */
bool SciIllLib::CGLInfo::CheckErrorFBO()
{
	GLenum errCode = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (errCode != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Error with fbo" << std::endl;
        return false;
	}
	return true;
}
