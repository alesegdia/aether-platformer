import os
import shutil
import sys

def copy_and_modify_folder(src_folder, dest_folder, game_name):
    if not os.path.exists(src_folder):
        print(f"Source folder '{src_folder}' does not exist.")
        return

    game_folder = os.path.join(dest_folder, game_name.lower())
    
    if os.path.exists(game_folder):
        print(f"Destination folder '{game_folder}' already exists.")
        return

    shutil.copytree(src_folder, game_folder)

    for root, dirs, files in os.walk(game_folder):
        for file_name in files:
            file_path = os.path.join(root, file_name)
            new_file_name = file_name.replace("Template", game_name)
            new_file_path = os.path.join(root, new_file_name)

            with open(file_path, 'r') as file:
                file_content = file.read()

            new_file_content = file_content.replace("##GAMENAME##", game_name)

            with open(new_file_path, 'w') as file:
                file.write(new_file_content)

            if new_file_path != file_path:
                os.remove(file_path)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python create-game.py <src_folder> <dest_folder> <game_name>")
        sys.exit(1)

    src_folder = sys.argv[1]
    dest_folder = sys.argv[2]
    game_name = sys.argv[3]

    copy_and_modify_folder(src_folder, dest_folder, game_name)