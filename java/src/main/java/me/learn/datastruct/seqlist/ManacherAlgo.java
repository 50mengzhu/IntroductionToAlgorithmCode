package me.learn.datastruct.seqlist;


/**
 * Manacher algorithm, used for solving the longest
 * Palindrome substring of a specific string
 *
 * @author mica
 */
public class ManacherAlgo {

    private static final String DELIM = "#";


    private String preDeal(String str) {
        StringBuilder sb = new StringBuilder(DELIM);
        for (char c : str.toCharArray()) {
            sb.append(c);
            sb.append(DELIM);
        }
        return sb.toString();
    }

    public void manacher(String str) {
        String afterDeal = preDeal(str);
        int[] radius = new int[afterDeal.length()];
        int symmetryAxis = 0;
        int rightBoundary = 0;
        for (int i = 1; i < afterDeal.length(); ++ i) {
            radius[i] = rightBoundary > i ?
                    Math.min(radius[2 * symmetryAxis - i], rightBoundary - i) : 1;
            while (i - radius[i] >= 0 && i + radius[i] < radius.length
                    && afterDeal.charAt(i - radius[i]) == afterDeal.charAt(i + radius[i])) {
                ++ radius[i];
            }
            // update symmetry axis and right boundary
            if (i + radius[i] > rightBoundary) {
                rightBoundary = i + radius[i];
                symmetryAxis = i;
            }
        }

        for (int i = 0; i < radius.length; ++ i) {
            System.out.println(radius[i]);
        }
    }


}
