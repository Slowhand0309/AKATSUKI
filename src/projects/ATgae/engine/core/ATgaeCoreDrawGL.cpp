#include "ATgae/engine/core/ATgaeCoreGL.h"

/**
 * Draw point.
 *
 * @param pointVec2 Point coordinate
 * @param color     Point color
 * @param size      Point size
 */
void ATCoreGL::drawPoint(ATVector2 &pointVec2, ATColor color, float size)
{
  const GLfloat vtx[] = {
    pointVec2[0], pointVec2[1]
  };
  glVertexPointer(2, GL_FLOAT, 0, vtx);
  glPointSize(size);
  AT2GLCOLOR(color);

  glMatrixMode(GL_MODELVIEW);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_POINTS, 0, 1);
  glDisableClientState(GL_VERTEX_ARRAY);
}

/**
 * Draw line.
 *
 * @param startVec2  Start coordinate
 * @param endVec2 End coordinate
 * @param color Line color
 * @param lineWidth Line width
 */
void ATCoreGL::drawLine(ATVector2 &startVec2, ATVector2 &endVec2, ATColor color, float lineWidth)
{
  const GLfloat vtx2[] = {
    startVec2[0], startVec2[1],
    endVec2[0], endVec2[1]
  };
  glVertexPointer(2, GL_FLOAT, 0, vtx2);
  glLineWidth(lineWidth);
  AT2GLCOLOR(color);

  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_LINES, 0, 2);
  glDisableClientState(GL_VERTEX_ARRAY);
}
