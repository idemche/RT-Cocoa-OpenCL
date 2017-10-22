NAME = RT


all: $(NAME)
	xcodebuild

$(NAME):
	@make -C RT/Model/Body

clean:
	@make -C RT/Model/Body clean

fclean:
	@make -C RT/Model/Body fclean
	@rm -rf build

re: fclean all

.PHONY: re fclean all clean
