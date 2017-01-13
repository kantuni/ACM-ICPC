import java.lang.reflect.Array;
import java.util.*;

public class RaggedyRaggedy {
    private static int L;
    private static ArrayList<String> words = new ArrayList<String>();
    private static Map<String, int[]> memo = new HashMap<String, int[]>();
    private static int lastLineWords;

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

        // out of bounds
        if (words.size() < j + 1) {
            return 0;
        }

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
    private static int[] c(int i, int k, int last) {
        ArrayList<Integer> raggedness = new ArrayList<Integer>();

        // out of bounds
        if (i > words.size() - 1 - last) {
            return new int[]{0, -1};
        }

        int l = i;
        while (w(i, l) > 0 && l <= words.size() - 1 - last) {
            // add value to memo
            if (!memo.containsKey((l + 1) + ", " + (k + 1))) {
                memo.put((l + 1) + ", " + (k + 1), c(l + 1, k + 1, last));
            }

            // calculate all raggedness values
            raggedness.add(r(i, l) + memo.get((l + 1) + ", " + (k + 1))[0]);
            l++;
        }

        // find a total minimum raggedness
        int minimum = Collections.min(raggedness);
        memo.put(i + ", " + k, new int[]{minimum, raggedness.indexOf(minimum)});

        return new int[]{minimum, raggedness.indexOf(minimum)};
    }

    /**
     * Calculate raggedness values with different number of last words and
     * return the minimum of them.
     *
     * @return minimum total raggedness and number of last line words
     */
    private static int[] minimizeTotalRaggedness() {
        // clean memo
        memo.clear();

        // set the min value to a raggedness with 1 last word
        int last = 1, i = 0;
        int minimum = c(0, 0, last)[0];

        while (i < words.size()) {
            // go as much as possible to find a minimum
            if (w(words.size() - i - 1, words.size() - 1) > 0 && w(words.size() - i - 1, words.size() - 1) <= L) {
                // clean memo
                memo.clear();
                // update minimum value
                if (minimum > c(0, 0, i)[0]) {
                    minimum = c(0, 0, i)[0];
                    last = i;
                }
            }
            i++;
        }

        // clean memo
        memo.clear();
        // call minimum once again to update memo
        c(0, 0, last);

        return new int[] {minimum, last};
    }


    /**
     * Build a string with a minimum total raggedness from a memo table
     *
     * @return string with minimum total raggedness
     */
    private static String backtracking() {
        String string = "";

        // start with first word, i.e. the last winner
        int i = 0, k = 0;
        int winnerIndex = memo.get(i + ", " + k)[1];

        while (winnerIndex > -1) {
            // add words to the appropriate line
            for (String word : words.subList(i, i + winnerIndex + 1)) {
                string += word + " ";
            }
            // remove trailing space
            string = string.substring(0, string.length() - 1);
            // move to next line
            string += "\n";

            // move to the next winner
            i += winnerIndex + 1;
            k += 1;
            winnerIndex = memo.get(i + ", " + k)[1];
        }

        // if there are last line words
        if (lastLineWords > 0) {
            for (String word : words.subList(words.size() - lastLineWords, words.size())) {
                string += word + " ";
            }
            // remove trailing space
            string = string.substring(0, string.length() - 1);
        }

        // remove empty line
        if (string.substring(string.length() - 1, string.length()).equals("\n")) {
            string = string.substring(0, string.length() - 1);
        }

        return string;
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

            int[] answer = minimizeTotalRaggedness();
            lastLineWords = answer[1];

            System.out.println(backtracking());
            System.out.println("===");
        }
    }
}
