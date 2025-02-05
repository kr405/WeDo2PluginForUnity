namespace WeDo2Sample
{
    public class ToggleButton : Button
    {
        protected bool isEnabled = false;

        protected override void OnClick()
        {
            isEnabled = !isEnabled;
        }
    }
}


