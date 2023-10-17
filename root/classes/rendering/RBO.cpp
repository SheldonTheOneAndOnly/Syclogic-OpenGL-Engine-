#include<classes/rendering/RBO.h>

RBO::RBO(Window window) {
	glGenRenderbuffers(1, &ID);
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window.width, window.height);
}

void RBO::Apply() {
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ID);

	auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Framebuffer error: " << status << std::endl;
	}
}

void RBO::Bind() {

}

void RBO::Unbind() {

}

void RBO::Destroy() {

}