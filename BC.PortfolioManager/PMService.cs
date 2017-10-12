using RabbitMQ.Client;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace BC.PortfolioManager
{
    public partial class PMService : ServiceBase
    {
        private Task updatePortfolio;
        private CancellationTokenSource cancellationTokenSource;

        private IConnection connection;
        private IModel channel;

        private int counter = 0;

        public PMService()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            var factory = new ConnectionFactory() { HostName = "localhost" };
            connection = factory.CreateConnection();
            channel = connection.CreateModel();

            channel.QueueDeclare(queue: "bcqueue",
                                durable: false,
                                exclusive: false,
                                autoDelete: false,
                                arguments: null);

            cancellationTokenSource = new CancellationTokenSource();
            updatePortfolio = Task.Run(() => UpdatePortfolio(cancellationTokenSource.Token));
        }

        protected override void OnStop()
        {
        }

        public async Task UpdatePortfolio(CancellationToken token)
        {
            while (true)
            {
                counter++;
                string msg = "Status "+counter;
                var body = Encoding.UTF8.GetBytes(msg);

                channel.BasicPublish(exchange: "",
                                     routingKey: "bcqueue",
                                     basicProperties: null,
                                     body: body);

                Random rnd = new Random();
                int delay = rnd.Next(100, 1000);

                await Task.Delay(TimeSpan.FromMilliseconds(delay), token);
            }
        }
    }
}
