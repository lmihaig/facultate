using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Xml;
using System.Xml.Linq;


namespace XML
{
    class Program
    {
        static string customerPath = @"C:\Users\Snow\source\repos\XML\XML\CustomersDetail.xml";
        static void Main(string[] args)
        {
            string fileName = @"C:\Users\mariu\Desktop\Lab3_MDS_Exemplu3_XML\XML\Orders.xml";
            parseWithXmlDocument(fileName);
            parseWithXmlReader(fileName);

            createXMLDocLINQ();
            //ShowNames();
            //ShowNames2();
            //AddElementLast();
            //AddElementFirst();
            //AddSpecific("1003");
            //DeleteElement("2000");
            //UpdateElement("1005");


            Console.ReadLine();
        }

        private static void parseWithXmlDocument(string fileName)
        {
            //5
            var sw = new Stopwatch();
            sw.Start();
            //6
            decimal totalOrderPrice = 0;
            decimal totalFreightCost = 0;
            decimal averageFreightCost = 0;
            decimal orderQty = 0;
            //7
            var doc = new XmlDocument();
            doc.Load(fileName);
            orderQty = doc.SelectNodes("//Order").Count;
            //8
            foreach (XmlNode node in doc.SelectNodes("//LineItem"))
            {
                var freight = decimal.Parse(node.Attributes["Freight"].Value);
                var linePrice = decimal.Parse(node.Attributes["Price"].Value) * decimal.Parse(node.Attributes["Qty"].Value);
                totalOrderPrice += linePrice + freight;
                totalFreightCost += freight;
            }
            //9
            Console.WriteLine("Total Order Price: {0:C}", totalOrderPrice);
            Console.WriteLine("Total Freight Cost: {0:C}", totalFreightCost);
            Console.WriteLine("Average Freight Cost per Order: {0:C}", totalFreightCost / orderQty);
            sw.Stop();
            Console.WriteLine("Time to Parse XmlDocument: {0}", sw.Elapsed);
            Console.WriteLine("---");
        }

        private static void parseWithXmlReader(string fileName)
        {
            var sw = new Stopwatch();
            sw.Start();
            decimal totalOrderPrice = 0;
            decimal totalFreightCost = 0;
            decimal averageFreightCost = 0;
            decimal orderQty = 0;
            using (var xmlReader = new XmlTextReader(fileName))
            {
                while (xmlReader.Read())
                {
                    if (xmlReader.NodeType == XmlNodeType.Element)
                    {
                        switch (xmlReader.Name)
                        {
                            case "Order":
                                ++orderQty;
                                break;
                            case "LineItem":
                                var qty = decimal.Parse(xmlReader.GetAttribute("Qty"));
                                var price = decimal.Parse(xmlReader.GetAttribute("Price"));
                                var freight = decimal.Parse(
                                xmlReader.GetAttribute("Freight"));
                                totalFreightCost += freight;
                                totalOrderPrice += (qty * price) + freight;
                                break;
                        }
                    }
                }
            }
            Console.WriteLine("Total Order Price: {0:C}", totalOrderPrice);
            Console.WriteLine("Total Freight Cost: {0:C}", totalFreightCost);
            Console.WriteLine("Average Freight Cost per Order: {0:C}", totalFreightCost / orderQty);
            sw.Stop();
            Console.WriteLine("Time to Parse XmlReader: {0}", sw.Elapsed);
        }

        private static void createXMLDocLINQ()
        {
            XDocument xmlDocument = new XDocument(
                new XDeclaration("1.0", "utf-8", "yes"),

                new XComment("LINQ To XML Demo"),

                new XElement("Customers",
                    new XElement("Customer", new XAttribute("CustID", 1001),
                        new XElement("Name", "Bob"),
                        new XElement("MobileNo", "0123456789"),
                        new XElement("Location", "New York City"),
                        new XElement("Address", "Crosby Street")),

                    new XElement("Customer", new XAttribute("CustID", 1002),
                        new XElement("Name", "Alice"),
                        new XElement("MobileNo", "2345678910"),
                        new XElement("Location", "London"),
                        new XElement("Address", "Abbey Road")),

                    new XElement("Customer", new XAttribute("CustID", 1003),
                        new XElement("Name", "Rohan"),
                        new XElement("MobileNo", "2356789410"),
                        new XElement("Location", "London"),
                        new XElement("Address", "Brick Lane")),

                    new XElement("Customer", new XAttribute("CustID", 1004),
                        new XElement("Name", "Anna"),
                        new XElement("MobileNo", "34567891230"),
                        new XElement("Location", "Berlin"),
                        new XElement("Address", "Warschauer Strasse"))
                        ));

            xmlDocument.Save(@"C:\Users\mariu\Desktop\Lab3_MDS_Exemplu3_XML\XML\CustomersDetail.xml");
            Console.WriteLine("XML creat!");
        }

        private static void ShowNames()
        {
            var doc = XDocument.Load(@"C:\Users\mariu\Desktop\Lab3_MDS_Exemplu3_XML\XML\CustomersDetail.xml");

            var names = from customers in doc.Descendants("Customer")
                        select customers.Element("Name").Value;

            foreach (string strName in names)
            {
                Console.WriteLine(strName);
            }
        }

        private static void ShowNames2()
        {
            var doc = XDocument.Load(@"C:\Users\mariu\Desktop\Lab3_MDS_Exemplu3_XML\XML\Orders.xml\CustomersDetail.xml");

            var names = from customers in doc.Element("Customers").Elements("Customer")
                        select customers.Element("Name").Value;

            foreach (string strName in names)
            {
                Console.WriteLine(strName);
            }
        }

        private static void AddElementLast()
        {
            XDocument doc = XDocument.Load(customerPath);

            //add - adauga la final
            doc.Element("Customers").Add(
               new XElement("Customer", new XAttribute("CustID", 1005),
               new XElement("Name", "Jonn"),
               new XElement("MobileNo", "992282760"),
               new XElement("Location", "London"),
               new XElement("Address", "34th street London")
            ));

            doc.Save(customerPath);

            Console.WriteLine("Customer added");
        }
        private static void AddElementFirst()
        {
            XDocument doc = XDocument.Load(customerPath);

            //add - adauga la inceput
            doc.Element("Customers").AddFirst(
               new XElement("Customer", new XAttribute("CustID", 1005),
               new XElement("Name", "George"),
               new XElement("MobileNo", "992255879"),
               new XElement("Location", "London"),
               new XElement("Address", "27th street London")
            ));

            doc.Save(customerPath);

            Console.WriteLine("Customer added");
        }

        private static void AddSpecific(string IDValue)
        {
            //si AddAfterSelf 
            XDocument doc = XDocument.Load(customerPath);
            doc.Element("Customers").Elements("Customer")
                .Where(X => X.Attribute("CustID").Value == IDValue).SingleOrDefault()
                .AddBeforeSelf(
                  new XElement("Customer", new XAttribute("CustID", 2000),
                  new XElement("Name", "David"),
                  new XElement("MobileNo", "9921123460"),
                  new XElement("Location", "London"),
                  new XElement("Address", "87th streat London")
            ));

            doc.Save(customerPath);

            Console.WriteLine("Customer added");
        }

        private static void DeleteElement(string IDValue)
        {
            XDocument doc = XDocument.Load(customerPath);

            doc.Root.Elements().Where(x => x.Attribute("CustID").Value == IDValue).FirstOrDefault().Remove();

            //var toDelete = (from c in doc.Descendants("Customer")
            //                where c.Attribute("CustID").Value == IDValue
            //                select c);
            //toDelete.SingleOrDefault().Remove();

            doc.Save(customerPath);
            Console.WriteLine(IDValue +  " Customer deleted");
        }


        private static void UpdateElement(string IDValue)
        {
            XDocument doc = XDocument.Load(customerPath);
            doc.Element("Customers").Elements("Customer").Where(X => X.Attribute("CustID").Value == IDValue).SingleOrDefault()
                                                                .SetElementValue("Mobile", 9090909090);

            //var toUpdate = (from c in doc.Descendants("Customer")
            //                where c.Attribute("CustID").Value == IDValue
            //                select c).SingleOrDefault();

            //toUpdate.SetElementValue("Mobile", 9090909090);

            doc.Save(customerPath);
            Console.WriteLine(IDValue + " Customer updated");
        }
        
    }
}
