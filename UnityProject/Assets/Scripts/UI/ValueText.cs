namespace WeDo2Sample
{
    public class ValueText : TextUI
    {
        /// <summary>
        /// �w��̒l���e�L�X�g�ɔ��f����.
        /// </summary>
        /// <typeparam name="T">�l�̌^.</typeparam>
        /// <param name="value">�e�L�X�g�ɔ��f����l.</param>
        public void UpdateText<T>(T value)
        {
            Text = value.ToString();
        }
    }
}