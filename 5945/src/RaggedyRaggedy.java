import java.util.*;

public class RaggedyRaggedy {
    private static int L;
    private static ArrayList<String> words = new ArrayList<String>();
    private static Map<String, ArrayList> memo = new HashMap<String, ArrayList>();

    /**
     * Define w(i,j) as the width of the line containing words i through j, inclusive,
     * plus one blank space between each pair of words.
     *
     * @param i starting position
     * @param j ending position
     * @return w(i, j) value or 0
     */
    private static int w(int i, int j) {
        int width = 0;

        for (String word : words.subList(i, j + 1)) {
            // length of a word + blank space
            width += word.length() + 1;
        }
        // remove last blank space
        width -= 1;

        return (width > 0 && width <= L) ? width : 0;
    }

    /**
     * Define the raggedness of a line containing words i though j as
     * r(i, j) = (L − w(i, j)) * (L − w(i, j))
     *
     * @param i starting position
     * @param j ending position
     * @return r(i, j) value
     */
    private static int r(int i, int j) {
        return (int) Math.pow(L - w(i, j), 2);
    }

    /**
     * Let C(i, k, last) denote minimum raggedness of a line k containing ith word ignoring last words.
     * Then C(i, k, last) = min(r(i, i) + C(i + 1, k + 1, last), r(i, i + 1) + C(i + 2, k + 1, last), ...)
     *
     * @param i    starting position
     * @param k    line
     * @param last number of words used in the last line
     * @return a minimum total raggedness and an index of the minimum value (the winner)
     */
    private static ArrayList<Integer> c(int i, int k, int last) {
        ArrayList<Integer> raggedness = new ArrayList<Integer>();
        return raggedness;
    }

    public static void main(String[] args) {
        while (true) {
            Scanner cin = new Scanner(System.in);
            L = Integer.parseInt(cin.nextLine());

            // a value of zero indicates the end of input
            if (L == 0) {
                break;
            }

            // maximum number of lines
            int numberOfLines = 250;
            while (numberOfLines > 0) {
                String[] wordsInLine = cin.nextLine().split(" ");

                // terminate by an empty line
                if (wordsInLine[0].trim().equals("")) {
                    break;
                }

                // add words from new line
                Collections.addAll(words, wordsInLine);
                numberOfLines--;
            }

            System.out.println(Arrays.toString(words.toArray()));
        }
    }
}
