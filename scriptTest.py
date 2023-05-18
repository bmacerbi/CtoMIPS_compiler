import os
import subprocess

def compile_program():
    # Compilação do programa
    subprocess.run(["bison", "-v", "parser.y"])
    subprocess.run(["flex", "scanner.l"])
    subprocess.run(["gcc", "-Wall", "-o", "compiler", "scanner.c", "parser.c", "tables.c", "types.c"])

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

def main():
    compile_program()
    run_tests()

if __name__ == "__main__":
    main()