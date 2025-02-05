namespace WeDo2Sample
{
    public class DeviceIdContent : TextContent
    {
        public void OnPointerDown()
        {
            DeviceController.Instance.SelectedDevice = Number;
        }
    }
}
