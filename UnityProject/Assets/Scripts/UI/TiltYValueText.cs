namespace WeDo2Sample
{
    public class TiltYValueText : ValueText
    {
        void Update()
        {
            UpdateText(DeviceController.Instance.TiltY);
        }
    }
}
