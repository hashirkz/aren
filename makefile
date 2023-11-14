read_img: read_img.c read_img.h
	gcc read_img.c -lSDL2 -lSDL2_image -o read_img

ascii: ascii.c ascii.h
	gcc ascii.c ascii.h -lm -o ascii

ascii_render: ascii_render.c ascii.c ascii.h read_img.c read_img.h
	gcc ascii_render.c ascii.c read_img.c -lSDL2 -lSDL2_image -lm -o ascii_render
	