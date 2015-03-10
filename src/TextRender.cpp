/*
 * TextRender.cpp
 *
 *  Created on: 2014-01-13
 *      Author: ovsoil
 */

#include "TextRender.h"

TextRender::TextRender()
{

}

TextRender::~TextRender()
{

}

void TextRender::AddText(const wchar_t *text, vec4 *color, vec2 *pen)
{
    float r = color->red, g = color->green, b = color->blue, a = color->alpha;
    for(size_t i = 0; i < wcslen(text); ++i )
    {
        texture_glyph_t *glyph = texture_font_get_glyph( font, text[i] );
        if( glyph != NULL )

        {
            float kerning = 0.0f;
            if( i > 0)
            {
                kerning = texture_glyph_get_kerning( glyph, text[i-1] );
            }
            pen->x += kerning;
            float x0  = ( pen->x + glyph->offset_x );
            float y0  = ( pen->y + glyph->offset_y );
            float x1  = ( x0 + glyph->width );
            float y1  = ( y0 - glyph->height );
            float s0 = glyph->s0;
            float t0 = glyph->t0;
            float s1 = glyph->s1;
            float t1 = glyph->t1;
            GLuint index = buffer->vertices->size;
            GLuint indices[] = {index, index+1, index+2,
                                index, index+2, index+3};
            vertex_t vertices[] = { { x0,y0,0,  s0,t0,  r,g,b,a },
                                    { x0,y1,0,  s0,t1,  r,g,b,a },
                                    { x1,y1,0,  s1,t1,  r,g,b,a },
                                    { x1,y0,0,  s1,t0,  r,g,b,a } };
            vertex_buffer_push_back_indices( buffer, indices, 6 );
            vertex_buffer_push_back_vertices( buffer, vertices, 4 );
            pen->x += glyph->advance_x;
        }
    }
}


void TextRender::SetupRC()
{
    initPrograms();
    initTextures();
    buffer = vertex_buffer_new( "vertex:3f,tex_coord:2f,color:4f" ); 
    vec4 color = {{1,1,0,1}};
    vec2 pen = {{0,0}};
    pen.y = -font->descender;
    for(size_t i=0; i<10; ++i )
    {
        pen.x = 10.0;
        AddText(text, &color, &pen );
        pen.y += font->height - font->linegap;
    }
}

void TextRender::Update()
{
    vec4 color = {{1,0,0,1}};
    vec2 pen = {{0,0}};
    vertex_buffer_clear( buffer );

    pen.y = -font->descender;
    for(size_t i=0; i<10; ++i )
    {
        pen.x = 10.0;
        AddText(text, &color, &pen );
        pen.y += font->height - font->linegap;
    }
}

void TextRender::Render()
{
    static int ii = 0;
    glBindTexture( GL_TEXTURE_2D, atlas->id );
    if(ii++ == 0)
    {
        for(int i = 0; i < 16; ++i)
        {
            cout << mvpMatrix[i] << ",";
        }
        cout << endl << shader << endl;
    }
    glUseProgram( shader );
    {
        glUniform1i( glGetUniformLocation( shader, "texUnit" ),
                     0 );
        glUniformMatrix4fv( glGetUniformLocation( shader, "MVP" ),
                            1, 0, mvpMatrix);
        vertex_buffer_render( buffer, GL_TRIANGLES );
    }
}

void TextRender::SetMVP(const M3DMatrix44f mvp)
{
    memcpy(mvpMatrix, mvp, sizeof(M3DMatrix44f));
    //mat4_set_identity( &projection );
    //mat4_set_identity( &model );
    //mat4_set_identity( &view );
}
