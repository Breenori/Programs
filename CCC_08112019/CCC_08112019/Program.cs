using System;
using System.Collections.Generic;

namespace CCC_08112019
{
    class Program
    {
        static void Main(string[] args)
        {
            int start_row = 0;
            int start_col = 0;
            int length = 1;
            int height = 1;
            int maxlength = 0;
            int maxheight = 0;
            int maxsize = 0;
            int a = 0;
            String[] lines = System.IO.File.ReadAllLines("../../../level3_1.in");
            int rows = Convert.ToInt32(lines[0].Split(" ")[0]);
            int cols = Convert.ToInt32(lines[0].Split(" ")[1]);
            

            List<int> datalist = new List<int>();

            for (int i = 1; i < rows; i++)
            {
                string[] alt_lines = lines[i].Split(" ");
                start_row = i;
                height = 1;

                for (int j = 0; j < cols - 1; j++)
                {
                    
                    a = i + height;
                    a = Convert.ToInt32(lines[i + height].Split(" ")[j]);
                    a = Convert.ToInt32(lines[i].Split(" ")[j]);

                    while ((i + height) < rows && (Convert.ToInt32(lines[i + height].Split(" ")[j]) == Convert.ToInt32(lines[i].Split(" ")[j])))
                    {
                        height++;
                    }

                    
                    bool tester = true;
                    for(int h = 0; h < height; h++)
                    {
                        tester = tester && (lines[i + h].Split(" ")[j] == lines[i + h].Split(" ")[j + 1]);
                    }

                    if (tester)
                    {
                        length++;

                        if (maxsize == length * height)
                        {
                            datalist.Add(start_col+1);
                            datalist.Add(start_row-1);
                        }
                        else if (maxsize < length * height)
                        {
                            maxsize = length * height;
                            datalist.Clear();
                            datalist.Add(start_col+1);
                            datalist.Add(start_row-1);
                        }
                    }
                    else
                    {
                        length = 1;
                        height = 1;
                        start_col = j;
                    }
                }
            }

            Console.Out.WriteLine(datalist.Count/2);
            for (int index = 0; index < datalist.Count-1; index += 2)
            {
                Console.Out.WriteLine(datalist[index] + " " + datalist[index+1]);
                System.IO.File.WriteAllText(@"C:\Users\basti\Desktop\abgabe.txt", datalist[index] + " " + datalist[index + 1]);
            }
        }
    }
}
