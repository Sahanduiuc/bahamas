using BC.PortfolioManager.Components;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace BC.PortfolioManager
{
    class TraderEngine
    {
        private Queue<PMEvent> eventsQueue;

        public TraderEngine(ref Queue<PMEvent> eventsQueue,
            PortfolioHandler portfolioManager
            )
        {
            this.eventsQueue = eventsQueue;
        }

        public void StartSession()
        {
            while (true)
            {
                // Get new data events from data stream
                if (!eventsQueue.Any())
                {

                }
                // Process Queue contents
                else
                {

                }

                Thread.Sleep(1000);
            }
        }
    }
}
