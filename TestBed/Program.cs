using BC.PortfolioManager;
using IBApi;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace TestBed
{
    class TestObg
    {
        public int MyProperty { get; set; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            TestObg t = new TestObg();
            t.MyProperty = 10;
            CHNG(t);

            //EWrapperImpl testImpl = new EWrapperImpl();
            //EClientSocket clientSocket = testImpl.ClientSocket;
            //EReaderSignal readerSignal = testImpl.Signal;
            ////! [connect]
            //clientSocket.eConnect("127.0.0.1", 7497, 0);

            ////Create a reader to consume messages from the TWS. The EReader will consume the incoming messages and put them in a queue
            //var reader = new EReader(clientSocket, readerSignal);
            //reader.Start();
            ////Once the messages are in the queue, an additional thread need to fetch them
            //new Thread(() => { while (clientSocket.IsConnected()) {
            //        readerSignal.waitForSignal(); reader.processMsgs();
            //    } }) { IsBackground = true }.Start();

            //while (testImpl.NextOrderId <= 0) { }

            //testIBMethods(clientSocket, testImpl.NextOrderId);

            ////Console.WriteLine("Disconnecting...");
            ////clientSocket.eDisconnect();

            Console.ReadKey();
            //return 0;
        }

        private static void CHNG(TestObg t)
        {
            t.MyProperty = t.MyProperty * 80;
        }

        private static void testIBMethods(EClientSocket client, int nextId)
        {
            marketDepthOperations(client);
        }

        public static Contract EurGbpFx()
        {
            //! [cashcontract]
            Contract contract = new Contract();
            contract.Symbol = "EUR";
            contract.SecType = "CASH";
            contract.Currency = "GBP";
            contract.Exchange = "IDEALPRO";
            //! [cashcontract]
            return contract;
        }

        private static void marketDepthOperations(EClientSocket client)
        {
            /*** Requesting the Deep Book ***/
            //! [reqmarketdepth]
            client.reqMarketDepth(2001, EurGbpFx(), 5, null);
            //! [reqmarketdepth]
            //Thread.Sleep(2000);
            /*** Canceling the Deep Book request ***/
            //! [cancelmktdepth]
            //client.cancelMktDepth(2001);
            //! [cancelmktdepth]
        }

        private static void realTimeBars(EClientSocket client)
        {
            /*** Requesting real time bars ***/
            //! [reqrealtimebars]
            client.reqRealTimeBars(3001, EurGbpFx(), 5, "MIDPOINT", false, null);
            //! [reqrealtimebars]
            //Thread.Sleep(1000);
            /*** Canceling real time bars ***/
            //! [cancelrealtimebars]
            //client.cancelRealTimeBars(3001);
            //! [cancelrealtimebars]
        }
    }
}
