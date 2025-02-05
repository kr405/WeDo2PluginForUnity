namespace WeDo2Sample
{
    public class ValueText : TextUI
    {
        /// <summary>
        /// 指定の値をテキストに反映する.
        /// </summary>
        /// <typeparam name="T">値の型.</typeparam>
        /// <param name="value">テキストに反映する値.</param>
        public void UpdateText<T>(T value)
        {
            Text = value.ToString();
        }
    }
}