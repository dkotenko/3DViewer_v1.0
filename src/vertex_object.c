#include "scop.h"


t_vao				vao_create(void)
{
	t_vao			vao;

	vao.attribute_next = 0;
	glGenVertexArrays(1, &vao.object);
	return (vao);
}

void				vao_destroy(t_vao *vao)
{
	int				i;

	i = 0;
	while (i < vao->attribute_next)
		vbo_destroy(vao->attribute_data + i++);
	glDeleteVertexArrays(1, &vao->object);
}

void				vao_bind(const t_vao *vao)
{
	glBindVertexArray(vao ? vao->object : 0);
}

void				vao_attribute(
					t_vao *vao,
					const t_vector *vector,
					int element_size)
{
	t_vbo			*vbo;

	ft_assert_critical(NULL,
		vao->attribute_next < SCOP_VAO_ATTRIBUTE_NUMBER,
		"Can't add more attributes to VAO");
	vbo = vao->attribute_data + vao->attribute_next;
	*vbo = vbo_create();
	vbo_bind(vbo);
	vbo_buffer(vector);
	glVertexAttribPointer(vao->attribute_next, element_size, GL_FLOAT,
		GL_FALSE, element_size * sizeof(float), NULL);
	glEnableVertexAttribArray(vao->attribute_next);
	vbo_bind(NULL);
	vao->attribute_next++;
}

t_vbo				vbo_create(void)
{
	t_vbo			vbo;

	glGenBuffers(1, &vbo);
	return (vbo);
}

void				vbo_destroy(t_vbo *vbo)
{
	glDeleteBuffers(1, vbo);
}

void				vbo_bind(const t_vbo *vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo ? *vbo : 0);
}

void				vbo_buffer(const t_vector *vector)
{
	glBufferData(GL_ARRAY_BUFFER, vector->length * vector->element_size,
		vector->storage, GL_STATIC_DRAW);
}
