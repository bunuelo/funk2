import cairo

width = 500
height = 500

def drawName(cr, name, x, y):
    cr.set_source_rgb(0.1, 0.1, 0.1)
    cr.select_font_face("Verdana", cairo.FONT_SLANT_NORMAL, cairo.FONT_WEIGHT_NORMAL)
    cr.set_font_size(0.02)

    x_bearing, y_bearing, x_span, y_span = cr.text_extents(name)[:4]
    cr.move_to(x - x_span / 2 - x_bearing, y - y_span / 2 - y_bearing)
    cr.show_text(name)

surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, width, height)
cr = cairo.Context(surface)
cr.scale(width, height)

cr.set_source_rgb(0.6, 0.6, 0.6)
cr.rectangle(0, 0, width, height)
cr.fill()

drawName(cr, 'derp', 0.5, 0.5)

surface.write_to_png('test.png')
