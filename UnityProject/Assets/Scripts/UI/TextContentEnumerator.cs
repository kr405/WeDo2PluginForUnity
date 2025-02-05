using UnityEngine;

namespace WeDo2Sample
{
    public class TextContentEnumerator : MonoBehaviour
    {
        [SerializeField] TextContent content;

        uint counter = 0;

        /// <summary>
        /// テキストを列挙する.
        /// </summary>
        /// <param name="texts">テキストの配列.</param>
        public virtual void Enumerate(string[] texts)
        {
            Clear();
            foreach (var text in texts)
            {
                Push(text);
            }
        }

        /// <summary>
        /// 列挙されているテキストを全て削除する.
        /// </summary>
        public virtual void Clear()
        {
            var contents = GetComponentsInChildren<TextContent>();
            foreach (var content in contents)
            {
                Remove(content);
            }
        }

        /// <summary>
        /// 新しいテキストを追加する.
        /// </summary>
        /// <param name="text">テキスト.</param>
        public virtual void Push(string text)
        {
            var obj = Instantiate(content);
            obj.Text = text;
            obj.transform.SetParent(transform);
            obj.Number = counter;
            counter++;
        }

        /// <summary>
        /// 指定したテキストを削除する.
        /// </summary>
        /// <param name="content">対象のテキスト.</param>
        public virtual void Remove(TextContent content)
        {
            Destroy(content.gameObject);
            counter--;
        }
    }
}


