import subprocess
import os
import glob

def runTester(file_in):
    with open(f'in/{file_in}', 'r') as f:
        conteudo = f.read()
    saida = subprocess.run('bin/./scanner', input=conteudo, shell=True, stdout=subprocess.PIPE, universal_newlines=True)

    with open(f'out/{file_in[:-2]}.txt', 'w') as f:
        f.write(saida.stdout)
    
    print(f"Saida de in/{file_in} escrita em out/{file_in[:-2]}.txt")


if __name__ == '__main__':
    print("Executando Testes...")
    os.makedirs(f'out', exist_ok=True)

    cFiles = glob.glob('in/*.c')
    
    for file in cFiles:
        runTester(file[3:])