using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Avtopark
{
    public partial class AvtobusiMarshruta : Form
    {
        public AvtobusiMarshruta(string marshrut)
        {
            InitializeComponent();
            LoadData(marshrut);
        }

        private void LoadData(string marshrut)
        {
            string connectString = @"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=" +
                @"C:\winformsDB\Avtopark\Database1.mdf;Integrated Security=True";

            SqlConnection myConnection = new SqlConnection(connectString);

            myConnection.Open();

            string query = "SELECT Автобус, Тип " +
                        "FROM [Автобусы] " +
                        "WHERE Автобусы.Автобус IN (SELECT Автобус " +
                                                    "FROM Водят " +
                                                    "WHERE Маршрут = @Маршрут)";

            SqlCommand command = new SqlCommand(query, myConnection);
            command.Parameters.AddWithValue("Маршрут", marshrut);

            try
            {
                SqlDataReader reader = command.ExecuteReader();

                List<string[]> data = new List<string[]>();

                while (reader.Read())
                {
                    data.Add(new string[2]);

                    data[data.Count - 1][0] = reader[0].ToString();
                    data[data.Count - 1][1] = reader[1].ToString();
                }

                reader.Close();

                myConnection.Close();

                foreach (string[] s in data)
                    dataGridView1.Rows.Add(s);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Oшибка!\n\n" + ex.Message, "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }
    }
}
