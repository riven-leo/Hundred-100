package turtle;

import java.util.List;
import java.util.ArrayList;

public class TurtleSoup {

    // Specification:函数开头的英文注释，描述每个函数的作用，以及传入的参数和返回值
    // 作用：调用者 contact 函数

    /**
     * Draw a square.
     * 
     * @param turtle the turtle context
     * @param sideLength length of each side
     */
    public static void drawSquare(Turtle turtle, int sideLength) {
        for (int i = 0; i < 4; i++) {
            turtle.forward(sideLength);
            turtle.turn(90);
        }
    }

    /**
     * Sides -> Interior Angle
     * 
     * @param sides number of sides, where sides must be > 2
     * @return angle in degrees, where 0 <= angle < 360
     */
    public static double calculateRegularPolygonAngle(int sides) {
        return (sides - 2) * 180.0 / sides;
    }

    /**
     * Interior Angle -> Sides
     */
    public static int calculatePolygonSidesFromAngle(double angle) {
        double exteriorAngle = 180 - angle;
        return (int) Math.round(360.0 / exteriorAngle);
    }

    /**
     * Given the number of sides, draw a regular polygon.
     */
    public static void drawRegularPolygon(Turtle turtle, int sides, int sideLength) {

        // Turtle 每画一条边之后需要转的是外角
        double interiorAngle = calculateRegularPolygonAngle(sides);
        double exteriorAngle = 180 - interiorAngle;

        for (int i = 0; i < sides; i++) {
            turtle.forward(sideLength);
            turtle.turn(exteriorAngle);
        }
    }

    /**
     * Calculate heading adjustment to point toward target.//point动词指向target
     * 
     * Turtle 的方向定义(坐标convention)：
     *
     *        0°
     *        ↑
     *
     * 270° ←   → 90°
     *
     *       180°
     *
     * (dy,dx)方向向量，atan2根据二维方向求它对应的角度 
     * atan2 通常以 x 轴为基准，即求从 x 轴逆时针旋转到目标方向的角度，atan2(dy, dx)。
     * 这里交换 dx / dy，使北方成为 0°。
     * 
     * Custom（看重历史和文化）
     * Convention（看重当下社会的默契和实用性）
     * rule 具有强制性和约束力，违反会有明确惩罚；
     */
    public static double calculateHeadingToPoint(
        double currentHeading, 
        int currentX, int currentY, 
        int targetX, int targetY
    ) {
        // 计算目标点的绝对朝向
        double targetHeading = Math.toDegrees(
                Math.atan2(
                        targetX - currentX,
                        targetY - currentY
                )
        );

        // atan2 可能返回负角度，统一转换到 [0,360)
        targetHeading = (targetHeading + 360) % 360;

        // Turtle 需要知道的是：
        // 从当前方向向右还要转多少度
        return (targetHeading - currentHeading + 360) % 360; //计算和产生副作用(绘图)被分开了。
    }

    /**
     * Calculate all heading adjustments between consecutive points.
     * consecutive 指“一个接一个”的独立事件或数字按顺序相连（有间隔或界限）
     * 而 continuous 指毫无间断、一刻不停的单一过程或状态
     */
    public static List<Double> calculateHeadings(
            List<Integer> xCoords,
            List<Integer> yCoords) {

        assert xCoords.size() == yCoords.size();

        List<Double> headings = new ArrayList<>();

        // Turtle 一开始朝北
        double currentHeading = 0.0;

        for (int i = 0; i < xCoords.size() - 1; i++) {

            double adjustment = calculateHeadingToPoint(
                    currentHeading,
                    xCoords.get(i),
                    yCoords.get(i),
                    xCoords.get(i + 1),
                    yCoords.get(i + 1)
            );

            // 记录每次转向的角度
            headings.add(adjustment);

            // 转完以后 Turtle 的绝对朝向也发生变化
            currentHeading =
                    (currentHeading + adjustment) % 360;
        }

        return headings;
    }

    /**
     * Draw personal art.
     */
    public static void drawPersonalArt(Turtle turtle) {

        // 定义要依次经过的点
        List<Integer> xCoords = new ArrayList<>();
        List<Integer> yCoords = new ArrayList<>();

        // 房子左下角
        xCoords.add(0);
        yCoords.add(0);

        // 左上角
        xCoords.add(0);
        yCoords.add(60);

        // 屋顶
        xCoords.add(40);
        yCoords.add(90);

        // 右上角
        xCoords.add(80);
        yCoords.add(60);

        // 右下角
        xCoords.add(80);
        yCoords.add(0);

        // 回到起点
        xCoords.add(0);
        yCoords.add(0);

        // 计算每一段路径需要转多少度
        List<Double> headings = calculateHeadings(xCoords, yCoords);

        // 根据 headings 真正控制 Turtle
        for (int i = 0; i < headings.size(); i++) {

            // 转向下一个点
            turtle.turn(headings.get(i));

            // 计算当前位置到下一个点的距离
            int dx = xCoords.get(i + 1) - xCoords.get(i);
            int dy = yCoords.get(i + 1) - yCoords.get(i);

            double distance = Math.sqrt(dx * dx + dy * dy);

            // Turtle.forward 要的是整数长度
            turtle.forward((int) Math.round(distance));
        }
    }

    public static void main(String args[]) {
        DrawableTurtle turtle = new DrawableTurtle();

        // 可以任选一个测试
        //drawSquare(turtle, 40);

        // drawRegularPolygon(turtle, 6, 50);

        drawPersonalArt(turtle);

        turtle.draw();
    }
}