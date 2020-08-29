using System;

namespace Grafo
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Exemplos:");
            Console.WriteLine("<{1,2,3,4},{1,2},{1,3},{2,3},{2,4},{3,4}>");
            Console.WriteLine("<{4},{1,2},{1,3},{2,3},{2,4},{3,4}>");
            Console.WriteLine("<{10},{1,2},{1,5},{1,6},{2,1},{2,3},{2,7},{3,2},{3,4},{3,8},{4,3},{4,5},{4,9},{5,1},{5,4},{5,10},{6,1},{6,8},{6,9},{7,2},{7,9},{7,10},{8,3},{8,6},{8,10},{9,4},{9,6},{9,7},{10,5},{10,7},{10,8}>\n");

            while (true)
            {
                string entry;
                int vertices = 0, n = -1;
                int[][] matrix;

                // get entry
                Console.Write("Digite sua entrada (0 para sair): ");
                entry = Console.ReadLine();
                if (entry.Equals("0")) break;
                for (var i = 0; i < entry.Length; i++)
                {
                    if (entry[i].Equals('}'))
                    {
                        entry = entry.Substring(i);
                        break;
                    }
                    if (char.IsDigit(entry[i]))
                    {
                        if (char.IsDigit(entry[i + 1]))
                        {
                            vertices = int.Parse(entry[i].ToString() + entry[i + 1].ToString());
                            i++;
                        }
                        else vertices = int.Parse(entry[i].ToString());
                    }
                }

                // initialize matrix
                matrix = new int[vertices][];
                for (var i = 0; i < vertices; i++)
                {
                    matrix[i] = new int[vertices];
                    for (int j = 0; j < vertices; j++)
                        matrix[i][j] = 0;
                }

                // create connections
                for (var i = 0; i < entry.Length; i++)
                {
                    if (char.IsDigit(entry[i]) && n == -1)
                    {

                        if (char.IsDigit(entry[i + 1]))
                        {
                            n = int.Parse(entry[i].ToString() + entry[i + 1].ToString());
                            i++;
                        }
                        else n = int.Parse(entry[i].ToString());
                    }
                    else if (char.IsDigit(entry[i]) && n != -1)
                    {
                        if (char.IsDigit(entry[i + 1]))
                        {
                            matrix[n - 1][int.Parse(entry[i].ToString() + entry[i + 1].ToString()) - 1] = 1;
                            i++;
                        }
                        else matrix[n - 1][int.Parse(entry[i].ToString()) - 1] = 1;
                        n = -1;
                    }
                }

                // print matrix
                Console.WriteLine("\nMatriz de adjacência:");
                Console.Write("   ");
                for (var i = 0; i < vertices; i++)
                    Console.Write(i + 1 + "  ");
                Console.WriteLine();
                for (var i = 0; i < vertices; i++)
                {
                    Console.Write(i + 1 + " ");
                    for (int j = 0; j < vertices; j++)
                        Console.Write("[" + matrix[i][j] + "]");
                    Console.WriteLine();
                }

                // print vector
                Console.WriteLine("\nVetor de adjacência:");
                for (var i = 0; i < vertices; i++)
                {
                    Console.Write(i + 1 + " [ ] -> ");
                    for (int j = 0; j < vertices; j++)
                        if (matrix[i][j] == 1)
                            Console.Write("[" + (j + 1) + "] -> ");
                    Console.WriteLine("null");
                }
                Console.ReadLine();
                Console.WriteLine("\n");
            }
        }
    }
}
