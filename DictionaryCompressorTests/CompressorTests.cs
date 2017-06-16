using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace DictionaryCompressorTests
{
    [TestClass]
    public class CompressorTests
    {
        [TestMethod]
        public void GetOrderTest()
        {
            //arrange 
            int expected = 0;
            //
            DictionaryCompressor.IOManager iOManager = new DictionaryCompressor.IOManager("file1.txt", "file2.txt");
            var result = iOManager.GetOrder();
            //
            Assert.AreEqual(result, expected);
        }

        [TestMethod]
        public void SetAndGetInputFileNameTest()
        {
            string expected = "newFilename";
            DictionaryCompressor.IOManager iOManager = new DictionaryCompressor.IOManager("file1.txt", "file2.txt");
            iOManager.SetInputFileName(expected);
            string result = iOManager.GetInputFileName();

            Assert.AreEqual(result, expected);
        }

        [TestMethod]
        public void SetAndGetOutputFileNameTest()
        {
            string expected = "newFilename";
            DictionaryCompressor.IOManager iOManager = new DictionaryCompressor.IOManager("file1.txt", "file2.txt");
            iOManager.SetInputFileName(expected);
            string result = iOManager.GetInputFileName();

            Assert.AreEqual(result, expected);
        }

        [TestMethod]
        public void FileCompleteTest()
        {
            bool expected = false;
            DictionaryCompressor.IOManager iOManager = new DictionaryCompressor.IOManager("file1.txt", "file2.txt");
            bool result = iOManager.IsFileCompletelyReadOut();

            Assert.AreEqual(result, expected);
        }

        [TestMethod]
        public void SetAndGetInputFileNameApplicationTest()
        {
            string expected = "newFilename";
            DictionaryCompressor.IOManager iOManager = new DictionaryCompressor.IOManager("file1.txt", "file2.txt");
            DictionaryCompressor.Application app = new DictionaryCompressor.Application(iOManager);
            app.SetInputFileName(expected);
            string result = app.GetInputFileName();

            Assert.AreEqual(result, expected);
        }

        [TestMethod]
        public void SetAndGetOutputFileNameApplicationTest()
        {
            string expected = "newFilename";
            DictionaryCompressor.IOManager iOManager = new DictionaryCompressor.IOManager("file1.txt", "file2.txt");
            DictionaryCompressor.Application app = new DictionaryCompressor.Application(iOManager);
            app.SetOutputFileName(expected);
            string result = app.GetOutputFileName();

            Assert.AreEqual(result, expected);
        }

    }
   
}
