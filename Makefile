NAME = RT

all: NAME

NAME:
	@open RT.xcodeproj
	@make -C RT/Model/Body

clean:
	@make -C RT/Model/Body clean

fclean:
	@make -C RT/Model/Body fclean

re: fclean all
