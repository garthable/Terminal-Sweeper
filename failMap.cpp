#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

#ifndef FAILMAP
#define FAILMAP

class failMap
{
    public:
        void addLoss(unsigned short x, unsigned short y)
        {
            m_lossData[x + y*m_sizeX] += 1;
        }
        unsigned long findMax()
        {
            unsigned long max = 0;
            for(unsigned long i : m_lossData)
                if (i > max)
                    max = i;
            return max;
        }
        void write()
        {
            std::ofstream file(m_fileName);
            if (!file.is_open())
                return;
            unsigned long max = findMax();
            std::string output = "";
            for(unsigned int i = 0; i < m_lossData.size(); i++)
            {
                unsigned long val = m_lossData[i];
                unsigned short index = (unsigned short)std::lerp(69.0, 0.0, (double)val/(double)max);
                output += m_asciiDither[index];
                output += ' ';
                if (i % m_sizeX == m_sizeX-1)
                    output += '\n';
            }

            output + '\n';

            double stepSize = (double)max/69.0;
            for (short i = 0; i < 70; i++)
            {
                output += m_asciiDither[i]; 

                output += " -> "; 
                output += std::to_string((unsigned long)((double)max - stepSize*i));
                if (std::to_string((unsigned long)((double)max - stepSize*i)).length() == 1)
                    output += " ";
                if (i % 5 == 0)
                    output += '\n';
                else
                    output += "     ";
            }

            output += '\n';
            std::vector<unsigned int> sortedIndexes;
            for (unsigned int i = 0; i < m_lossData.size(); i++)
                sortedIndexes.push_back(i);
            
            for (unsigned int i = 0; i < m_lossData.size(); i++)
                for (unsigned int j = 0; j < m_lossData.size(); j++)
                {
                    unsigned long a = m_lossData[sortedIndexes[i]];
                    unsigned long b = m_lossData[sortedIndexes[j]];

                    unsigned int _i = sortedIndexes[i];
                    unsigned int _j = sortedIndexes[j];

                    if (a > b)
                    {
                        sortedIndexes[i] = _j;
                        sortedIndexes[j] = _i;
                    }
                }
            
            for (unsigned int i : sortedIndexes)
            {
                unsigned short x = i % m_sizeX;
                unsigned short y = i / m_sizeX;
                output += "x: " + std::to_string(x) + " y: " + std::to_string(y) + " lossCount: " + std::to_string(m_lossData[i]);
                output += '\n';
            }
            file << output << std::endl;
            file.close();
        }
        failMap(unsigned short sizeX, unsigned short sizeY)
        {
            m_sizeX = sizeX;
            m_sizeY = sizeY;
            m_lossData.reserve(m_sizeX*m_sizeY);
            for (int i = 0; i < m_sizeX*m_sizeY; i++)
                m_lossData.push_back(0);
        }
    private:
        unsigned short m_sizeX;
        unsigned short m_sizeY;
        std::vector<unsigned long> m_lossData;
        
        std::string m_asciiDither = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
        std::string m_fileName = "failMap.txt";
};

#endif