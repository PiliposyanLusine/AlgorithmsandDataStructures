#include <iostream>
#include <string>

class GapBuffer
{
    private:

        static const int DefaultGapSize = 20;
        char* buffStart;
        char* gapStart;
        char* gapEnd;
        char* buffEnd;
        char* point;


        void expendBuff(int size)
        {
            char* originBuf = buffStart;
            int newSize = buffEnd - buffStart + size + DefaultGapSize;
            buffStart = (char*) realloc (buffStart, newSize);
            gapStart += buffStart - originBuf;
            gapEnd += buffStart - originBuf;
            point += buffStart - originBuf;
            buffEnd = buffStart + newSize;
        }


        void expendGap(int size)
        {   
            expendBuff(size);
            gapEnd += size;
        }


        void copyBytes(char* from, char* to, int length)
        {
            if(to > from)
            {
                to += length;
                from += length;
                while(length--)
                {
                    *(to--) = *(from--);
                }
            }
            else
            {
                while(length--)
                {
                    *(to++) = *(from++);
                }
            }
        }


    public:


        GapBuffer() 
        {
            buffStart = (char*) malloc(DefaultGapSize);
            gapStart = buffStart;
            gapEnd = buffStart + DefaultGapSize;
            buffEnd = gapEnd;
            point = buffStart;
        }

        void moveGapToPoint()
        {
            if(point < gapStart)
            {
                copyBytes(point, (gapEnd - gapStart + point), (gapEnd - gapStart));
                gapEnd = point + (gapEnd - gapStart);
                gapStart = point;
            }
            else
            {
                copyBytes(point, gapStart, (point - gapEnd));
                gapStart = point - (gapEnd - gapStart);
                gapEnd = point;
                point = gapStart;
            }
        }



        void insert(char ch)
        {
            if(gapStart != point)
            {
                moveGapToPoint();
            }
            if((gapEnd - gapStart) == 0)
            {
                expendGap(DefaultGapSize);
            }
            *gapStart++ = ch;
            point++;
        }



        void insert(const std::string& str)
        {
            if(str.length() > (gapEnd - gapStart))
            {
                expendGap(str.length());
                for(int i = 0; i < str.length(); ++i)
                {
                    insert(str[i]);
                }
            }
        } 


        int getGapSize()
        {
            return gapEnd - gapStart;
        }


        int getBuffSize()
        {
            return buffEnd - buffStart;
        } 


        void remove(int lenth)
        {
            if(gapStart != point)
            {
                moveGapToPoint();
            }
            gapEnd += lenth;
        }


        void setPoint(int offset)
        {
            point = buffStart + offset;
            if(point > gapStart && point < gapEnd)
            {
                point += gapEnd - gapStart;
            }
        }


        void printGap()
        {
            char* tmp = buffStart;
            while (tmp != buffEnd)
            {
                if(tmp > gapStart && tmp < gapEnd)
                {
                    std::cout << "&" << std::endl;
                }
                else
                {
                    std::cout << *tmp << std::endl;
                }
                ++tmp;
            }
            
        }
};

int main()
{
    GapBuffer g;
    g.insert("hello");
    g.setPoint(12);
    g.insert("world");
    g.printGap();
}