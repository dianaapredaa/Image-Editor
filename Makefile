# Copyright 2021 - 2022 Preda Diana 314CA

build:
	gcc -g image_editor.c load_action.c save_action.c select_action.c exit_action.c utils.c crop_action.c rotate_action.c apply_action.c -lm -Wall -Wextra -o image_editor
clean:
	rm -f image_editor
