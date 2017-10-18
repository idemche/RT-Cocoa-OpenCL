# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admin <admin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 19:14:50 by hshakula          #+#    #+#              #
#    Updated: 2017/10/18 14:24:03 by admin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/
LIB_PATH = ./lib/

SUB_FOLDERS = parsing server client client/kernel math 

SRC_NAME =	parsing/parse_cam.c \
			parsing/parse_objects.c \
			parsing/parse_objects_2.c \
			parsing/parse_objects_3.c \
			parsing/parse_objects_4.c \
			parsing/parse_objects_5.c \
			parsing/parse_objects_6.c \
			parsing/parse_objects_7.c \
			parsing/parse_objects_8.c \
			parsing/parse_objects_9.c \
			parsing/parse_object_info.c \
			parsing/parse_material.c \
			parsing/parse_spotlights.c \
			parsing/parse_scene.c \
			parsing/parse_util.c \
			parsing/parse_textures.c \
			parsing/parse_textures_.c \
			parsing/parse_textures__.c \
			parsing/parse_video_sequence.c \
			parsing/parse_environment.c \
			parsing/parse_negative_obj.c \
			parsing/matrix_init.c \
			parsing/scene_validate.c \
			client/loop.c \
			client/init.c \
			client/main.c \
			client/render.c \
			client/render_scene.c \
			client/update.c \
			server/util.c \
			client/kernel/kernel_init.c \
			client/kernel/alloc_buffer.c \
			client/kernel/write_buffer.c \
			client/kernel/set_args.c \
			client/kernel/kernel_util.c \
			client/kernel/kernel_release.c \
			math/quaternion.c \
			math/quaternion_.c \
			math/matrix.c \
			depth_map.c \
			util.c \
			perlin.c \
			perlin_.c \
			init.c \
			image.c
OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME =	cJSON \
			lodepng \
			libft \
			hdrReader

LIB_A = $(addsuffix .a, $(LIB_NAME))
LIB_FOLDERS = $(addprefix $(LIB_PATH), $(LIB_NAME))

FLAGS= -g -Wall -Werror -Wextra
FRAMEWORK = -F /Library/Frameworks -framework SDL2 -framework OpenGL -framework Appkit -framework OpenCL
CC = gcc
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB = ./lib/cJSON/cJSON.a ./lib/lodepng/lodepng.a ./lib/libft/libft.a ./lib/hdrReader/hdrReader.a
INC = $(addprefix -I, $(INC_PATH)) -I /Library/Frameworks/SDL2.framework/Headers $(addprefix -I, $(LIB_FOLDERS))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_PATH)/cJSON
	@make -C $(LIB_PATH)/lodepng
	@make -C $(LIB_PATH)/libft
	@make -C $(LIB_PATH)/hdrReader
	$(CC) $(FLAGS) $(FRAMEWORK) $(INC) $(LIB) $(OBJ) -o $(NAME)
	@clear
	@echo "༼ つ ◕_◕ ༽つ༼ つ ◕_◕ ༽つ༼ つ ◕_◕ ༽つ༼ つ ◕_◕ ༽つ༼ つ ◕_◕ ༽つ༼ つ ◕_◕ ༽つ༼ つ ◕_◕ ༽つ༼ つ ◕_◕ ༽つ༼ つ ◕_◕ ༽つ"
	@echo "                                                                                                  "
	@echo "RRRRRRRRRRRRRRRRR        TTTTTTTTTTTTTTTTTTTTTTT       iiii                   hhhhhhh             "
	@echo "R::::::::::::::::R       T:::::::::::::::::::::T      i::::i                  h:::::h             "
	@echo "R::::::RRRRRR:::::R      T:::::::::::::::::::::T       iiii                   h:::::h             "
	@echo "RR:::::R     R:::::R     T:::::TT:::::::TT:::::T                              h:::::h             "
	@echo "  R::::R     R:::::R     TTTTTT  T:::::T  TTTTTT     iiiiiii     ssssssssss    h::::h hhhhh       "
	@echo "  R::::R     R:::::R             T:::::T             i:::::i   ss::::::::::s   h::::hh:::::hhh    "
	@echo "  R::::RRRRRR:::::R              T:::::T              i::::i ss:::::::::::::s  h::::::::::::::hh  "
	@echo "  R:::::::::::::RR               T:::::T              i::::i s::::::ssss:::::s h:::::::hhh::::::h "
	@echo "  R::::RRRRRR:::::R              T:::::T              i::::i  s:::::s  ssssss  h::::::h   h::::::h"
	@echo "  R::::R     R:::::R             T:::::T              i::::i    s::::::s       h:::::h     h:::::h"
	@echo "  R::::R     R:::::R             T:::::T              i::::i       s::::::s    h:::::h     h:::::h"
	@echo "  R::::R     R:::::R             T:::::T              i::::i ssssss   s:::::s  h:::::h     h:::::h"
	@echo "RR:::::R     R:::::R           TT:::::::TT           i::::::is:::::ssss::::::s h:::::h     h:::::h"
	@echo "R::::::R     R:::::R           T:::::::::T           i::::::is::::::::::::::s  h:::::h     h:::::h"
	@echo "R::::::R     R:::::R           T:::::::::T           i::::::i s:::::::::::ss   h:::::h     h:::::h"
	@echo "RRRRRRRR     RRRRRRR           TTTTTTTTTTT           iiiiiiii  sssssssssss     hhhhhhh     hhhhhhh"
	@echo "                                                                                                  "
	@echo "(づ￣ ³￣)づ(づ￣ ³￣)づ(づ￣ ³￣)づ(づ￣ ³￣)づ(づ￣ ³￣)づ(づ￣ ³￣)づ(づ￣ ³￣)づ(づ￣ ³￣)づ(づ￣ ³￣)づ"
	@echo "Usage:"
	@echo "As server: ./RT 'pathToScene'"
	@echo "As client: ./RT 'client'"
	@echo "To validate scene enter: ./RT 'pathToScene' 'validate'"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(addprefix $(OBJ_PATH), $(SUB_FOLDERS))
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	@make -C $(LIB_PATH)/cJSON clean
	@make -C $(LIB_PATH)/lodepng clean
	@make -C $(LIB_PATH)/libft clean
	@make -C $(LIB_PATH)/hdrReader clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH)/cJSON fclean
	@make -C $(LIB_PATH)/lodepng fclean
	@make -C $(LIB_PATH)/libft fclean
	@make -C $(LIB_PATH)/hdrReader fclean
	@rm -f $(NAME)
	@rm -f RT.zip

re: fclean all

clean_o:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)

re_o: clean_o all

zip:
	zip -rX RT.zip ./ -x textures/\* .git/\*

.PHONY: re fclean all clean zip
