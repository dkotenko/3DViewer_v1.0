#include <stdio.h>
#include <math.h>

#include <glib.h>
#include <epoxy/gl.h>

#include "graph.h"
#include "ui.h"
#include "scop.h"


extern t_scop scop;

void on_realize(GtkGLArea* gl_area) {
	gtk_gl_area_make_current(gl_area);

	// Print version info:
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
	g_print("Renderer: %s\n", renderer);
	g_print("OpenGL version supported %s\n", version);
	g_print("GLSL version supported %s\n", glsl_version);

	if (gtk_gl_area_get_error(gl_area) != NULL)  {
		return;
	}

	// Enable depth buffer:
	gtk_gl_area_set_has_depth_buffer(gl_area, TRUE);
	// Enable alpha:
//	gtk_gl_area_set_has_alpha(gl_area, TRUE);

	/* Init buffers */
	init(&scop, scop.filename);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	//glEnable(GL_DEPTH_TEST); // enable depth-testing
	//glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	/* Enable blending */
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	// Get frame clock:
	GdkGLContext*	glcontext = gtk_gl_area_get_context(gl_area);
	GdkWindow*		glwindow = gdk_gl_context_get_window(glcontext);
	GdkFrameClock*	frame_clock = gdk_window_get_frame_clock(glwindow);

	// Connect update signal:
	g_signal_connect_swapped(
				frame_clock,
				"update",
				G_CALLBACK(gtk_gl_area_queue_render),
				gl_area
				);

	// Start updating:
	gdk_frame_clock_begin_updating(frame_clock);

	g_print("OK\n");
}

gboolean on_render() {
	render_scene(&scop);

	// Don't propagate signal
	return TRUE;
}


/*
void on_resize(GtkGLArea* gl_area, int width, int height) {
}
*/

