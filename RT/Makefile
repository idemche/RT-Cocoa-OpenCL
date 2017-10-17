.PHONY: directories

NAME = RT
MKDIR_P = mkdir -p
CC = clang
SOURCES = main.m
OUT_DIR = Build
FRAMEWORKS := -framework Foundation -framework Cocoa -framework AppKit
LIBRARIES := -lobjc
CFLAGS = -Wall -Werror -g -v $(SOURCES) -O0
LDFLAGS = $(LIBRARIES) $(FRAMEWORKS) 
OUT = -o $(OUT_DIR)/$(NAME)

all: directories $(SOURCES) $(OUT)

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

$(OUT): $(OBJECTS)
	$(CC) -o $(OBJECTS) $@ $(CFLAGS) $(LDFLAGS) $(OUT)

.m.o: 
	$(CC) -c -Wall $< -o $@

fclean:
	rm -rf OUT
