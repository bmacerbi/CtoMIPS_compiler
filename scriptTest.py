import os
import subprocess

def compile_program():
    # Compilação do programa
    subprocess.run(["bison", "-v", "parser.y"])
    subprocess.run(["flex", "scanner.l"])
    subprocess.run(["gcc", "-Wall", "-o", "compiler", "scanner.c", "parser.c", "tables.c", "types.c", "ast.c", "interpreter.c"])


def delete_dot(path):
    for file in os.listdir(path):
        if file.endswith(".dot"):
            complete_path = os.path.join(path, file)
            os.remove(complete_path)

def run_tests():
    # Leitura dos arquivos de entrada
    input_files = os.listdir("in")

    for file in input_files:
        # Execução do programa para cada arquivo de entrada
        input_path = os.path.join("in", file)
        output_path = os.path.join("out", f"{file[:-2]}.txt")
       
        command = f"./compiler < {input_path}"
        result = subprocess.run(command, shell=True, capture_output=True, text=True)

        with open(output_path, "w") as output_file:
            output_file.write(result.stdout)
        
        print(f"Saida de {input_path} escrita em {output_path}")
        

        output_tree = os.path.join("treeOut", f"{file[:-2]}.dot")
        output_pdf = os.path.join("treeOut", f"{file[:-2]}.pdf")
        command_dot = f"./compiler < {input_path} 2> {output_tree}"
        command_pdf = f"dot -Tpdf {output_tree} -o {output_pdf}"

        subprocess.run(command_dot, shell=True, capture_output=True, text=True)
        subprocess.run(command_pdf, shell=True, capture_output=True, text=True)        


def main():
    compile_program()
    run_tests()
    delete_dot("treeOut")

if __name__ == "__main__":
    main()