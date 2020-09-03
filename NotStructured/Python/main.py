import numpy as np

if __name__ == '__main__':
    print('Exemplos:')
    print('<{1,2,3,4},{1,2},{1,3},{2,3},{2,4},{3,4}>')
    print('<{4},{1,2},{1,3},{2,3},{2,4},{3,4}>')
    print('<{10},{1,2},{1,5},{1,6},{2,1},{2,3},{2,7},{3,2},{3,4},{3,8},{4,3},{4,5},{4,9},{5,1},{5,4},{5,10},'
          '{6,1},{6,8},{6,9},{7,2},{7,9},{7,10},{8,3},{8,6},{8,10},{9,4},{9,6},{9,7},{10,5},{10,7},{10,8}>\n')

    while True:
        # get entry
        entry = input('Digite sua entrada (0 para sair): ')
        if entry == '0': break

        # check vertex amount
        vertices = 0
        for i in range(len(entry)):
            if entry[i] == '}':
                entry = entry[i:]
                break
            if entry[i].isdigit():
                if entry[i + 1].isdigit():
                    vertices = int(entry[i] + entry[i + 1])
                    i += 1
                else: vertices = int(entry[i])

        # create connections
        matrix = np.zeros((vertices, vertices), dtype=int)
        n = -1
        for i in range(len(entry)):
            if entry[i].isdigit() and n == -1:
                if entry[i + 1].isdigit():
                    n = int(entry[i] + entry[i + 1])
                    i += 1
                else: n = int(entry[i])
            elif entry[i].isdigit() and n != -1:
                if entry[i + 1].isdigit():
                    matrix[n - 1][int(entry[i] + entry[i + 1]) - 1] = 1
                    i += 1
                else: matrix[n - 1][int(entry[i]) - 1] = 1
                n = -1

        # print matrix
        print('\nMatriz de adjacência:')
        print('    ', end='')
        for i in range(vertices):
            print(i + 1, end='   ')
        print()
        for i in range(vertices):
            print(i + 1, end=' ')
            for j in range(vertices):
                print('[', matrix[i][j], end=']')
            print()

        # print vector
        print('\nVetor de adjacência:')
        for i in range(vertices):
            print(i + 1, end=' [ ] -> ')
            for j in range(vertices):
                if matrix[i][j] == 1:
                    print('[', j + 1, end='] -> ')
            print('null')
        print('\n')
        input()
