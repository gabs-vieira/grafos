import sys

def dfs(no_inicial, nivel_atual, niveis, grafo, nos):
    niveis[no_inicial] = nivel_atual
    for i in range(nos):
        if grafo[no_inicial][i] == 1 and niveis[i] == -1:
            grafo[no_inicial][i] = 2
            grafo[i][no_inicial] = 0
            dfs(i, nivel_atual + 1, niveis, grafo, nos)

def lowpt(no_inicial, pontos_baixos, niveis, grafo, nos):
    for de in range(1, nos):
        for para in range(1, nos):
            if grafo[de][para] == 1 and niveis[de] < niveis[para]:
                grafo[de][para] = 0

    if pontos_baixos[no_inicial] != -1:
        return pontos_baixos[no_inicial]

    pontos_baixos[no_inicial] = no_inicial

    for i in range(1, nos + 1):
        if grafo[no_inicial][i] == 2 and niveis[lowpt(i, pontos_baixos, niveis, grafo, nos)] < niveis[pontos_baixos[no_inicial]]:
            pontos_baixos[no_inicial] = pontos_baixos[i]
        elif grafo[no_inicial][i] == 1 and niveis[i] < niveis[pontos_baixos[no_inicial]]:
            pontos_baixos[no_inicial] = i

    return pontos_baixos[no_inicial]

def imprimir_grafo(grafo, nos):
    for i in range(nos):
        for j in range(nos):
            print(grafo[i][j], end=' ')
        print()

def ler_grafo(arquivo, nos, arestas):
    grafo = [[0] * nos for _ in range(nos)]

    for _ in range(arestas):
        de, para = map(int, arquivo.readline().split())
        grafo[de][para] = 1
        grafo[para][de] = 1

    return grafo

def destruir_grafo(grafo, nos):
    pass  

def imprimir_pontos_baixos(pontos_baixos, nos):
    print("pontos baixos: ", end='')
    for i in range(nos):
        print(f"{i}:{pontos_baixos[i]} ", end='')
    print()

def imprimir_pontes(grafo, pontos_baixos, nos):
    tem_ponte = False
    print("pontes: ", end='')

    for de in range(1, nos):
        for para in range(1, nos):
            if grafo[de][para] == 2 and pontos_baixos[para] == para:
                tem_ponte = True
                print(f"({de},{para}) ", end='')

    if not tem_ponte:
        print("nenhuma", end='')

    print()

def imprimir_articulacoes(articulacoes, nos):
    tem_articulacao = False
    print("articulações: ", end='')
    for i in range(nos):
        if articulacoes[i] != 0:
            tem_articulacao = True
            print(f"{articulacoes[i]} ", end='')

    if not tem_articulacao:
        print("nenhuma", end='')

    print()

def imprimir_marcadores(marcadores, nos):
    tem_marcadores = False
    print("marcadores: ", end='')
    for i in range(nos):
        if marcadores[i] != 0:
            tem_marcadores = True
            print(f"{marcadores[i]} ", end='')

    if not tem_marcadores:
        print("nenhum", end='')

    print()

def imprimir_bicomponentes(grafo, marcadores, articulacoes, raiz, nos):
    print("bicomponentes: ", end='')

    for i in range(nos - 1, 0, -1):
        articulacao = articulacoes[i]
        if articulacao != 0:
            print(f"{{|{articulacao}", end='')
            for de in range(articulacao, nos):
                for para in range(1, nos):
                    if grafo[de][para] == 2:
                        print(f"|{para}", end='')
                        grafo[de][para] = 0
            print("|}", end='')

    tem_bicomponentes = any(marcadores[i] != 0 for i in range(nos))

    if tem_bicomponentes:
        print(f" {{|{raiz}", end='')
        for de in range(1, nos):
            for para in range(1, nos):
                if grafo[de][para] == 2:
                    print(f"|{para}", end='')
        print("|}\n", end='')

    print()

def main():
    with open("input.txt", "r") as arquivo:
        contador_grafos = int(arquivo.readline().strip())

        for _ in range(contador_grafos):
            nos, arestas = map(int, arquivo.readline().split())
            nos += 1

            grafo = ler_grafo(arquivo, nos, arestas)

            niveis = [-1] * nos
            pontos_baixos = [-1] * nos

            dfs(1, 0, niveis, grafo, nos)
            lowpt(1, pontos_baixos, niveis, grafo, nos)

            marcadores = [0] * nos
            articulacoes = [0] * nos

            raiz = 1
            filhos = sum(1 for para in range(1, nos) if grafo[raiz][para] == 2)
            if filhos > 1:
                articulacoes[raiz] = raiz

            for de in range(1, nos):
                for para in range(1, nos):
                    if grafo[de][para] == 2 and (pontos_baixos[para] == de or pontos_baixos[para] == para):
                        marcadores[de] = para
                        if de != raiz:
                            articulacoes[de] = de

            imprimir_pontos_baixos(pontos_baixos, nos)
            imprimir_pontes(grafo, pontos_baixos, nos)
            imprimir_articulacoes(articulacoes, nos)
            imprimir_marcadores(marcadores, nos)
            imprimir_bicomponentes(grafo, marcadores, articulacoes, raiz, nos)

if __name__ == "__main__":
    main()
