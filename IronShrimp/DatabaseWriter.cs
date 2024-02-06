using Npgsql;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IronShrimp
{
    class DatabaseWriter
    {
        private NpgsqlConnection connection;

        public DatabaseWriter(string connectionString)
        {
            connection = new NpgsqlConnection(connectionString);
            connection.Open();
        }

        public bool InsertDatxFile(Datx metadata)
        {
            // TODO: Instead of DO NOTHING, consider DO UPDATE and indicate which fields to update
            string cmd = String.Format("INSERT INTO datx (filepath, filename) VALUES ('{0}', '{1}') ON CONFLICT DO NOTHING;", metadata.EscapedFilePath, metadata.Filename);

            Console.WriteLine(String.Format("\nAttempting to write: {0}\n", cmd));

            NpgsqlCommand command = new NpgsqlCommand(cmd, connection);
            return command.ExecuteNonQuery() > 0;
        }
    }
}
