using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using SortProject.Sorter.MergerSorter;
using System.Collections.Generic;
using SortProject.Sorter.ShellSorter;

namespace SortProjectTest
{

    [ TestClass ]
    public class SortMergeTest
    {
        List<int> ordered = new List<int> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        List<int> orderDesc = new List<int> { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
        List<int> unordered = new List<int> { 12, 10, 11, 5, 6, 8, 7, 4, 9, 15, 0, 1, 14, 13, 2, 3 };
        LinearMergeSorter<int> linearMergeSorter = new LinearMergeSorter<int>();
        LinearShellSorter<int> linearShellSorter = new LinearShellSorter<int>();
        ParallelMergeSorter<int> parallelMergeSorter = new ParallelMergeSorter<int>();

        [TestMethod]
        public void LinearMerge_OrederedList()
        {
            linearMergeSorter.Lst = ordered ;
            linearMergeSorter.Sort();
            var result = linearMergeSorter.Lst;
            CollectionAssert.AreEqual( ordered, result );
        }

        [TestMethod]
        public void LinearMerge_OrderDescList()
        {
            linearMergeSorter.Lst = orderDesc;
            linearMergeSorter.Sort();
            var result = linearMergeSorter.Lst;
            CollectionAssert.AreEqual( ordered, result );
        }

        [TestMethod]
        public void LinearMerge_UnorderedDescList()
        {
            linearMergeSorter.Lst = unordered;
            linearMergeSorter.Sort();
            var result = linearMergeSorter.Lst;
            CollectionAssert.AreEqual( ordered, result );
        }

        [TestMethod]
        public void LinearShell_OrederedList()
        {
            linearShellSorter.Lst = ordered;
            linearShellSorter.Sort();
            var result = linearShellSorter.Lst;
            CollectionAssert.AreEqual( ordered, result );
        }

        [TestMethod]
        public void LinearShell_OrderDescList()
        {
            linearShellSorter.Lst = orderDesc;
            linearShellSorter.Sort();
            var result = linearShellSorter.Lst;
            CollectionAssert.AreEqual( ordered, result );
        }

        [TestMethod]
        public void LinearShell_UnorderedDescList()
        {
            linearShellSorter.Lst = unordered;
            linearShellSorter.Sort();
            var result = linearShellSorter.Lst;
            CollectionAssert.AreEqual( ordered, result );
        }

        [TestMethod]
        public void ParallelMerge_OrederedList()
        {
            parallelMergeSorter.Lst = ordered;
            parallelMergeSorter.Sort();
            var result = parallelMergeSorter.Lst;
            CollectionAssert.AreEqual( ordered, result );
        }

        [TestMethod]
        public void ParallelMerge_OrderDescList()
        {
            parallelMergeSorter.Lst = orderDesc;
            parallelMergeSorter.Sort();
            var result = parallelMergeSorter.Lst;
            CollectionAssert.AreEqual( ordered, result );
        }

        [TestMethod]
        public void ParallelMerge_UnorderedDescList()
        {
            parallelMergeSorter.Lst = unordered;
            parallelMergeSorter.Sort();
            var result = parallelMergeSorter.Lst;
            CollectionAssert.AreEqual( ordered, result );
        }
    }
}
