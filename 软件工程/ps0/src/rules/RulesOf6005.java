package rules;

/**
 * RulesOf6005 represents the collaboration policy of 6.005 as described by the
 * general information on Stellar.
 */
public class RulesOf6005 {
     
    /**
     * Judge whether a given piece of code may be used in an assignment (problem
     * set or team project) or not, according to the 6.005 collaboration policy.
     * 
     * @param writtenByYourself true if the code in question was written by
     *        yourself or, in the case of a team project, your teammates,
     *        otherwise false.
     *          
     *          whether [or not可选] 是否，表达两方面，让我回答
     * @param availableToOthers if not writtenByYourself, whether or not the
     *        code in question is available to all other students in the class.
     *        Otherwise ignored.
     * @param writtenAsCourseWork if not writtenByYourself, whether or not the
     *        code in question was written specifically as part of a solution to
     *        a 6.005 assignment, in the current or past semesters. Otherwise
     *        ignored.
     * @param citingYourSource if not writtenByYourself, whether or not you
     *        properly cite your source. Otherwise ignored.
     * @param implementationRequired whether the assignment specifically asks
     *        you to implement the feature in question.
     * @return Whether or not, based on the information provided in the
     *         arguments, you are likely to be allowed to use the code in
     *         question in your assignment, according to the 6.005 collaboration
     *         policy for the current semester.
     */
    
    public static boolean mayUseCodeInAssignment(boolean writtenByYourself,
            boolean availableToOthers, boolean writtenAsCourseWork,
            boolean citingYourSource, boolean implementationRequired) {
        
        // 自己或队友写的代码，可以使用
        if (writtenByYourself) {
            return true;
        }

        // 别人的代码必须是所有同学都可以获得的
        if (!availableToOthers) {
            return false;
        }

        // 别人为 6.005 作业写的代码，不能使用
        if (writtenAsCourseWork) {
            return false;
        }

        // 使用外部代码必须注明来源
        if (!citingYourSource) {
            return false;
        }

        // 如果题目明确要求自己实现这个功能，
        // 就不能直接使用别人实现好的代码
        if (implementationRequired) {
            return false;
        }

        return true;
    }
    
    /**
     * Main method of the class.
     * 
     * Runs the mayUseCodeInAssignment method.
     * 
     * @param args unused
     */
    public static void main(String[] args) {
        System.out.println("You may certainly use code you wrote yourself: " +
            RulesOf6005.mayUseCodeInAssignment(true, false, true, true, true));
    }
}
