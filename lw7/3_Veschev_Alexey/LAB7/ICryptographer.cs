using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LAB7
{
    interface ICryptographer
    {
        void EncipherCaesar(int key);
        void EncipherGamma(string message);
        List<char> GetMessage();
    }
}
