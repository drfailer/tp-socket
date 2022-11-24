import java.io.*;import java.net.*;

public class Client {
  private static int port;
  public static void main (String [] args) throws Exception {
    String adresse, line, lineReversed;
    Reader readSoc;
    PrintStream a_envoye=null;

    adresse = "turing";
    port = Integer.parseInt("9876");
    Socket socket = new Socket(adresse, port);
    Reader reader = new InputStreamReader(System.in);
    BufferedReader keyboard = new BufferedReader(reader);
    a_envoye = new PrintStream(socket.getOutputStream());
    readSoc = new InputStreamReader(socket.getInputStream());
    BufferedReader RecuSoc = new BufferedReader (readSoc);

    while (true) {
      // System.out.print("choisir option\n0 - doublement\n1 - valeur\n2 - exit\nanwer> ");
      System.out.println("Entrez une ligne de texte : ");
      line = keyboard.readLine();
      line += "0";
      a_envoye.println(line);
      // si on a tape "FIN" on quitte le client
      if(line.equals("FIN")) break;
      lineReversed = RecuSoc.readLine();
      System.out.println("Recu : " + lineReversed);
    }
    // fermeture de la socket
    socket.close();
  }
}
